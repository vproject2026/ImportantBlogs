# One `@PostConstruct` or Multiple Methods: Which Is Better?

When a bean requires several initialization steps, we have two possible designs to choose from. 

## Approach 1: Multiple Annotated Methods

```java
@PostConstruct
void loadConfiguration() {}

@PostConstruct
void initializeCache() {}

@PostConstruct
void validateState() {}
```

## Approach 2: A Single Orchestrator Method

A single lifecycle method that delegates to regular private methods:

```java
@PostConstruct
void initialize() {
    loadConfiguration();
    initializeCache();
    validateState();
}

private void loadConfiguration() {}

private void initializeCache() {}

private void validateState() {}
```

> **Verdict:** The single `@PostConstruct` method is the better approach.

---

## Why the Single Method is Better

### 1. Specification Compliance
The Jakarta specification states that **only one method** in a given class can be annotated with `@PostConstruct`. The container invokes it after dependency injection and before putting the bean into service.

Some frameworks, including Spring, may execute multiple annotated methods. However, depending on this behavior makes the code less portable and can introduce uncertainty about execution order.

### 2. Execution-Time Difference
Lifecycle methods are normally discovered and invoked by the framework using reflection.

With three annotated methods, the invocation model is approximately:

```text
Container → reflective invocation of loadConfiguration()
Container → reflective invocation of initializeCache()
Container → reflective invocation of validateState()
```

With one orchestrator, it becomes:

```text
Container → reflective invocation of initialize()
  └── initialize() → direct call to loadConfiguration()
  └── initialize() → direct call to initializeCache()
  └── initialize() → direct call to validateState()
```

A previously referenced JMH microbenchmark measured approximately **7.1 ns** for cached reflective invocation and **3.7 ns** for direct invocation. (“Cached” means the `Method` metadata has already been located and retained, but `Method.invoke()` is still used to execute it).

*Note: These numbers should only illustrate the relative overhead. They are not measurements of Spring’s `@PostConstruct` processing, and actual results depend on the JDK, hardware, JVM warm-up, and framework version.*

### 3. CPU Utilization
The single-orchestrator design uses marginally less CPU because it crosses the reflective invocation boundary once. Its helper methods use ordinary calls that the JVM may optimize or inline.

Nevertheless, this difference is normally insignificant. `@PostConstruct` runs only during bean creation, not for every application request. Database queries, network calls, file reads, parsing, and cache construction will dominate initialization time.

> ⚠️ **Important:** The most critical consideration is **keeping initialization short**. Spring executes `@PostConstruct` within the singleton-creation lock, and the bean is not considered ready until the method returns.

---

## Recommendation

Use **one clearly named `@PostConstruct` method** and delegate to focused helper methods. This provides:

- ✅ **Specification compliance**
- ✅ **Explicit and deterministic ordering**
- ✅ **Slightly lower invocation overhead**
- ✅ **Easier testing and maintenance**
- ✅ **Clearer failure behavior**

*Choose this design mainly for correctness and clarity—the performance improvement is real but usually negligible.*
