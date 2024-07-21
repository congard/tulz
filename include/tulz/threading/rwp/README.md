# Readers-Writers Problem

We want to prevent more than one thread modifying the shared
resource simultaneously and allow for two or more readers to
access the shared resource at the same time, i.e.

- There can be multiple reader locks at the same time,
- but only one writer lock at any given moment.

## Fairness

The implementation satisfies fairness by using FIFO-based queue:

1. if the queue is empty, readers will be allowed to
   acquire the resource immediately,
2. if the queue is empty, only one writer will be allowed
   to acquire the resource at the same time,
3. if the queue is non-empty or the resource is busy,
   lock requests will be added to the queue.

## Examples

See tests: _tests/tulz/threading/rwp_.
