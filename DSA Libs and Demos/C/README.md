# Collections Library + Demonstration of Common Algorithms
### TODO: Move this to a separate repository
### Fundamental Principles
1. Don't expose the underlying implementation to the user. Use [opaque types](https://stackoverflow.com/questions/2301454/what-defines-an-opaque-type-in-c-and-when-are-they-necessary-and-or-useful).
2. APIs should be orthogonal except when there are extremely common functionalities for which providing an extra non-orthogonal function would be significantly more convenient.
   - There doesn't seem to be a common definition for an "orthogonal API", so I'll explain what I mean here in the follow two points.
   - The API is orthogonal if its functions do not overlap in behavior. Another way to look at it is the API is _not_ orthogonal if the behavior of one function can actually be done by another function.
   - An example of non-orthogonal API functions might be an `InsertAt(idx, val)` and `InsertAtEnd(val)` when a `Length()` method exists, because you could technically do `InsertAtEnd()` using `InsertAt( Length() )` (within a 0-indexed scheme).
   - The above `InsertAtEnd` example is one of the non-orthogonal functions I actually do include within the [`vector` API](./vector/vector.h), simply for its clear convenience.