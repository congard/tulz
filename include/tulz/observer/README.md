# Tulz::Observer

Basic implementation of the [observer pattern](https://en.wikipedia.org/wiki/Observer_pattern).

Note: `Subject` is not thread safe

## Usage

For more examples, see tests.

### Subject

```c++
Subject subject;

auto sub1 = subject.subscribe([]() {
    cout << "subscription1\n";
});

auto sub2 = subject.subscribe([]() {
    cout << "subscription2\n";
});

subject.notify();

sub2.unsubscribe();

subject.notify();
```

Output:

```
subscription1
subscription2
subscription1
```

<br>

```cpp
Subject<float> subject;
subject.subscribe([](float val) {
    cout << "value: " << val << "\n";
});

subject.notify(3.14f);
subject.notify(6.28f);
```

Output:

```
value: 3.14
value: 6.28
```

### Observable

```c++
ObservableInt val {0};
val.subscribe([](int val) {
    std::cout << "Value changed: " << val << "\n";
});

val = 5;
--val;
```

Output:

```
Value changed: 5
Value changed: 4
```

## TODO

It might be worth implementing:

1. `SynchronizedSubject` - thread-safe version of `Subject`
2. `ParallelSubject` - `SynchronizedSubject` that notifies observers in a parallel way
