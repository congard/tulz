# Tulz::Observer

Basic implementation of the [observer pattern](https://en.wikipedia.org/wiki/Observer_pattern).

Note: `Subject` is not thread safe

## Usage

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

## TODO

It might be worth implementing:

1. `SynchronizedSubject` - thread-safe version of `Subject`
2. `ParallelSubject` - `SynchronizedSubject` that notifies observers in a parallel way
