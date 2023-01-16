#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <functional>

/* <compose> */
template <typename B>
auto compose() {
  return [](B x) { return x; };
}

template <typename F>
auto compose(F f) {
  return [f](auto x) { return f(x); };
}

template <typename F, typename... Gs>
auto compose(F f, Gs... args) {
  return [f, args...](auto x) { return compose<Gs...>(args...)(f(x)); };
}

/* </compose> */

/* <lift> */
/*
lift h = \p -> h
lift h f = \p -> h (f p)
lift h f g = \p -> h (f p) (g p)
*/
template <typename P, typename H>
auto lift(H h) {
  return [h]([[maybe_unused]] P p) { return h; };
}

template <typename P, typename H, typename... Fs>
auto lift(H h, Fs... fs) {
  return [h, fs...](P p) { return h(fs(p)...); };
}

/* </lift> */

#endif /* FUNCTIONAL_H */