# Tulz::Observer

Basic implementation of the [observer pattern](https://en.wikipedia.org/wiki/Observer_pattern).

Note: `Subject` is not thread safe

## Usage

```c++
Subject subject;

ObserverFunction observerFunction0([]() {
    cout << "observerFunction0\n";
});

subject.subscribe(&observerFunction0);

{
    ObserverFunction observerFunction1([]() {
        cout << "observerFunction1\n";
    });

    ObserverFunction observerFunction2([]() {
        cout << "observerFunction2\n";
    });

    subject.subscribe(&observerFunction1);
    subject.subscribe(&observerFunction2);

    subject.notifyAll();
}

subject.notifyAll();
```

Output:

```
observerFunction0
observerFunction1
observerFunction2
observerFunction0
```

## TODO

It might be worth implementing:

1. `SynchronizedSubject` - thread-safe version of `Subject`
2. `ParallelSubject` - `SynchronizedSubject` that notifies observers in a parallel way
