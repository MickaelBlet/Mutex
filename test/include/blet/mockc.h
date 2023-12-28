/**
 * MockC
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2021-2023 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MOCKC_H_
#define _MOCKC_H_

#include <dlfcn.h>
#include <gmock/gmock.h>

#define MOCKC_CAT_IMPL_(x, y) x##y
#define MOCKC_CAT_(x, y) MOCKC_CAT_IMPL_(x, y)
#define MOCKC_CAT2_(x, y, z) MOCKC_CAT_(MOCKC_CAT_(x, y), z)
#define MOCKC_STRINGIFY_(x) #x
#define MOCKC_TO_STRING_(x) MOCKC_STRINGIFY_(x)

#define MOCKC_REPEAT_0_(m, f) /* nothing */
#define MOCKC_REPEAT_1_(m, f) m(1, f)
#define MOCKC_REPEAT_2_(m, f) MOCKC_REPEAT_1_(m, f), m(2, f)
#define MOCKC_REPEAT_3_(m, f) MOCKC_REPEAT_2_(m, f), m(3, f)
#define MOCKC_REPEAT_4_(m, f) MOCKC_REPEAT_3_(m, f), m(4, f)
#define MOCKC_REPEAT_5_(m, f) MOCKC_REPEAT_4_(m, f), m(5, f)
#define MOCKC_REPEAT_6_(m, f) MOCKC_REPEAT_5_(m, f), m(6, f)
#define MOCKC_REPEAT_7_(m, f) MOCKC_REPEAT_6_(m, f), m(7, f)
#define MOCKC_REPEAT_8_(m, f) MOCKC_REPEAT_7_(m, f), m(8, f)
#define MOCKC_REPEAT_9_(m, f) MOCKC_REPEAT_8_(m, f), m(9, f)
#define MOCKC_REPEAT_10_(m, f) MOCKC_REPEAT_9_(m, f), m(10, f)

#define MOCKC_ARG_(i, f) MOCKC_CAT_(var_, i)
#define MOCKC_ARG_DECLARATION_(i, f) GMOCK_ARG_(, i, f) MOCKC_ARG_(i, f)

#define MOCKC_INSTANCE(n)                                                      \
    ((MOCKC_CAT_(MockC_, n)::instance())                                       \
         ? *(MOCKC_CAT_(MockC_, n)::instance())                                \
         : (throw MockC_InstanceNotFound(__FILE__, MOCKC_TO_STRING_(__LINE__), \
                                         MOCKC_TO_STRING_(n)),                 \
            *(MOCKC_CAT_(MockC_, n)::instance())))

#define MOCKC_NEW_INSTANCE(n) \
    MOCKC_CAT_(MockC_, n) MOCKC_CAT_(local_instance_, n)

#define MOCKC_METHOD0(n, f) MOCKC_(0, n, f)
#define MOCKC_METHOD1(n, f) MOCKC_(1, n, f)
#define MOCKC_METHOD2(n, f) MOCKC_(2, n, f)
#define MOCKC_METHOD3(n, f) MOCKC_(3, n, f)
#define MOCKC_METHOD4(n, f) MOCKC_(4, n, f)
#define MOCKC_METHOD5(n, f) MOCKC_(5, n, f)
#define MOCKC_METHOD6(n, f) MOCKC_(6, n, f)
#define MOCKC_METHOD7(n, f) MOCKC_(7, n, f)
#define MOCKC_METHOD8(n, f) MOCKC_(8, n, f)
#define MOCKC_METHOD9(n, f) MOCKC_(9, n, f)
#define MOCKC_METHOD10(n, f) MOCKC_(10, n, f)
#define MOCKC_ATTRIBUTE_METHOD0(n, f, a) MOCKC_ATTRIBUTE_(0, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD1(n, f, a) MOCKC_ATTRIBUTE_(1, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD2(n, f, a) MOCKC_ATTRIBUTE_(2, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD3(n, f, a) MOCKC_ATTRIBUTE_(3, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD4(n, f, a) MOCKC_ATTRIBUTE_(4, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD5(n, f, a) MOCKC_ATTRIBUTE_(5, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD6(n, f, a) MOCKC_ATTRIBUTE_(6, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD7(n, f, a) MOCKC_ATTRIBUTE_(7, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD8(n, f, a) MOCKC_ATTRIBUTE_(8, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD9(n, f, a) MOCKC_ATTRIBUTE_(9, n, f, a)
#define MOCKC_ATTRIBUTE_METHOD10(n, f, a) MOCKC_ATTRIBUTE_(10, n, f, a)

#define MOCKC_EXPECT_CALL(n, p) EXPECT_CALL(MOCKC_INSTANCE(n), n p)

#if __cplusplus >= 201103L
#define MOCKC_DECLTYPE_METHOD0(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD0(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD1(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD1(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD2(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD2(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD3(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD3(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD4(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD4(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD5(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD5(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD6(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD6(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD7(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD7(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD8(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD8(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD9(n)                 \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD9(n, MOCKC_CAT_(decltype_, n))
#define MOCKC_DECLTYPE_METHOD10(n)                \
    using MOCKC_CAT_(decltype_, n) = decltype(n); \
    MOCKC_METHOD10(n, MOCKC_CAT_(decltype_, n))
#else
#define MOCKC_DECLTYPE_METHOD0()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD1()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD2()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD3()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD4()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD5()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD6()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD7()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD8()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD9()  /* not supported with version < cpp11 */
#define MOCKC_DECLTYPE_METHOD10() /* not supported with version < cpp11 */
#endif                            // __cplusplus >= 201103L

struct MockC_InstanceNotFound : public std::exception {
    MockC_InstanceNotFound(const char* file, const char* line,
                           const char* name) throw() {
        _message = file;
        _message += ":";
        _message += line;
        _message += " MockC '";
        _message += name;
        _message += "' instance not found.";
    }
    virtual ~MockC_InstanceNotFound() throw() {}
    const char* what() const throw() {
        return _message.c_str();
    }
    std::string _message;
};
struct MockC_RealFunctionNotFound : public std::exception {
    MockC_RealFunctionNotFound(const char* file, const char* line,
                               const char* name) throw() {
        _message = file;
        _message += ":";
        _message += line;
        _message += " MockC '";
        _message += name;
        _message += "' real function not found.";
    }
    virtual ~MockC_RealFunctionNotFound() throw() {}
    const char* what() const throw() {
        return _message.c_str();
    }
    std::string _message;
};

template<typename T>
struct MockC_Guard {
    MockC_Guard(T& instance) :
        _instance(instance) {
        _instance.isActive = true;
    }
    ~MockC_Guard() {
        _instance.isActive = false;
    }
    T& _instance;
};
template<typename T>
struct MockC_GuardReverse {
    MockC_GuardReverse(T& instance) :
        _instance(instance) {
        _instance.isActive = false;
    }
    ~MockC_GuardReverse() {
        _instance.isActive = true;
    }
    T& _instance;
};

template<typename T>
struct MockC_Singleton {
    static T*& instance() {
        static T* singleton = NULL;
        return singleton;
    }
};
template<typename T>
struct MockC_InstanceGuard {
    MockC_InstanceGuard(T& instance) :
        _instance(instance) {
        T::instance() = &_instance;
    }
    ~MockC_InstanceGuard() {
        T::instance() = NULL;
    }
    T& _instance;
};

#define MOCKC_GUARD(n)                                         \
    MockC_Guard<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuard_, \
                                                  n)(MOCKC_INSTANCE(n))
#define MOCKC_GUARD_REVERSE(n)                                               \
    MockC_GuardReverse<MOCKC_CAT_(MockC_, n)> MOCKC_CAT_(mockCGuardReverse_, \
                                                         n)(MOCKC_INSTANCE(n))
#define MOCKC_ENABLE(n) MOCKC_INSTANCE(n).isActive = true;
#define MOCKC_DISABLE(n) MOCKC_INSTANCE(n).isActive = false;

#define MOCKC_(i, n, f)       \
    MOCKC_CLASS_(i, n, f);    \
    MOCKC_REAL_FUNC_(i, n, f) \
    MOCKC_FAKE_FUNC_(i, n, f)

#define MOCKC_ATTRIBUTE_(i, n, f, a) \
    MOCKC_CLASS_(i, n, f);           \
    MOCKC_REAL_FUNC_(i, n, f)        \
    MOCKC_FAKE_FUNC_ATTRIBUTE_(i, n, f, a)

#define MOCKC_REAL_FUNC_(i, n, f)                                      \
    typedef GMOCK_RESULT_(, f) (*MOCKC_CAT2_(mockc_func_, n, _t))(     \
        MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f));  \
    static MOCKC_CAT2_(mockc_func_, n, _t)                             \
        MOCKC_CAT2_(mockc_real_func_, n, _singleton)() {               \
        static MOCKC_CAT2_(mockc_func_, n, _t)                         \
            MOCKC_CAT_(mockc_real_func_, n) =                          \
                (MOCKC_CAT2_(mockc_func_, n, _t))dlsym(RTLD_NEXT, #n); \
        return MOCKC_CAT_(mockc_real_func_, n);                        \
    }

#define MOCKC_CLASS_(i, n, f)                           \
    struct MOCKC_CAT_(MockC_, n) :                      \
        public MockC_Singleton<MOCKC_CAT_(MockC_, n)> { \
        MOCKC_CAT_(MockC_, n)                           \
        () :                                            \
            isActive(false) {                           \
            instance() = this;                          \
            return;                                     \
        }                                               \
        ~MOCKC_CAT_(MockC_, n)() {                      \
            instance() = NULL;                          \
            return;                                     \
        }                                               \
        MOCKC_CAT_(MOCK_METHOD, i)(n, f);               \
        bool isActive;                                  \
    }

#define MOCKC_FAKE_FUNC_(i, n, f)                                              \
    GMOCK_RESULT_(, f)                                                         \
    n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f)) {           \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) { \
            MOCKC_GUARD_REVERSE(n);                                            \
            return MOCKC_INSTANCE(n).n(                                        \
                MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));              \
        }                                                                      \
        if (MOCKC_CAT2_(mockc_real_func_, n, _singleton)() == NULL) {          \
            throw MockC_RealFunctionNotFound(                                  \
                __FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n));    \
        }                                                                      \
        return MOCKC_CAT2_(mockc_real_func_, n, _singleton)()(                 \
            MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));                  \
    }                                                                          \
    struct MOCKC_CAT_(MockC_, n)

#define MOCKC_FAKE_FUNC_ATTRIBUTE_(i, n, f, a)                                 \
    GMOCK_RESULT_(, f)                                                         \
    n(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_DECLARATION_, f)) a {         \
        if (MOCKC_CAT_(MockC_, n)::instance() && MOCKC_INSTANCE(n).isActive) { \
            MOCKC_GUARD_REVERSE(n);                                            \
            return MOCKC_INSTANCE(n).n(                                        \
                MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f));              \
        }                                                                      \
        if (MOCKC_CAT_(mockc_real_func_, n) == NULL) {                         \
            throw MockC_RealFunctionNotFound(                                  \
                __FILE__, MOCKC_TO_STRING_(__LINE__), MOCKC_TO_STRING_(n));    \
        }                                                                      \
        return MOCKC_CAT_(mockc_real_func_,                                    \
                          n)(MOCKC_CAT2_(MOCKC_REPEAT_, i, _)(MOCKC_ARG_, f)); \
    }                                                                          \
    struct MOCKC_CAT_(MockC_, n)

#endif // _MOCKC_H_