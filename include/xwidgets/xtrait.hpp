#include <iostream>
#include <string>
#include <functional>

#ifndef XWIDGETS_TRAIT
#define XWIDGETS_TRAIT

template <class T>
class trait {
public:

	using value_type = T;

	trait(const std::string& name, const T& init) : 
		m_name(name),
		m_data(init)
	{

	}

	template <class IV, class X>
	trait(const std::string& name,
		  IV&& init,
		  void(X::*observer)(const trait<T>&) const,
		  X* parent
		) :
		m_name(name),
		m_data(std::forward<IV>(init)),
		m_observer({std::bind(observer, parent, std::placeholders::_1)})
	{
	}

	template <class IV, class V, class X>
	trait(const std::string& name,
		  IV&& init,
		  V&& validator,
		  void(X::*observer)(const trait<T>&) const,
		  X* parent
		) :
		m_name(name),
		m_data(std::forward<IV>(init)),
		m_validator({validator}),
		m_observer({std::bind(observer, parent, std::placeholders::_1)})
	{
	}

	const std::string& name() const
	{
		return m_name;
	}

	T& ref() noexcept
	{
		return m_data;
	}

	const T& ref() const noexcept
	{
		return m_data;
	}

	operator T&() noexcept
	{
		return m_data;
	}

	operator const T& () const noexcept
	{
		return m_data;
	}

	const T& operator()() const noexcept
	{
		return m_data;
	}

	T& operator()() noexcept
	{
		return m_data;
	}

	template <class X>
	trait<T>& operator=(X&& new_data)
	{
		T proposal(std::forward<X>(new_data));
		if (m_validator.size())
		{
			for (auto& v : m_validator)
			{
				v(proposal);
			}
		}
		m_data = std::move(proposal);
		if (m_observer.size()) {
			for (auto& o : m_observer) {
				o(*this);
			}
		}
		return *this;
	}

	template <class X>
	void add_observer(X&& func)
	{
		m_observer.push_back(std::forward<X>(func));
	}

	template <class X>
	void add_observer(void(X::*func)(const trait<T>&), X* parent)
	{
		m_observer.push_back(std::bind(func, parent, std::placeholders::_1));
	}

	template <class X>
	void add_validator(X&& func)
	{
		m_validator.push_back(std::forward<X>(func));
	}

	template <class X>
	void add_validator(void(X::*func)(const trait<T>&), X* parent)
	{
		m_validator.push_back(std::bind(func, parent, std::placeholders::_1));
	}

private:
	T m_data;
	const std::string m_name;
	void* m_parent;
	std::vector<std::function<void(T&)>> m_validator;
	std::vector<std::function<void(const trait<T>&)>> m_observer;
};


#define XTRAIT_NODEFAULT(T, D, N) \
	trait<T> N = trait<T>(#N, T(), &D::notify, this);

#define XTRAIT_DEFAULT(T, D, N, V) \
	trait<T> N = trait<T>(#N, T(V), &D::notify, this);

#define XTRAIT_GENERAL(T, D, N, V, Validator) \
	trait<T> N = trait<T>(#N, T(V), Validator, &D::notify, this);

#define XTRAIT_OVERLOAD(_1, _2, _3, _4, _5, NAME, ...) NAME

#ifdef _MSC_VER
// Workaround for MSVC not expanding macros
#define XTRAIT_EXPAND(x) x
#define XTRAIT(...) XTRAIT_EXPAND(XTRAIT_OVERLOAD(__VA_ARGS__, XTRAIT_GENERAL, XTRAIT_DEFAULT, XTRAIT_NODEFAULT)(__VA_ARGS__))
#else
#define XTRAIT(...) XTRAIT_OVERLOAD(__VA_ARGS__, XTRAIT_GENERAL, XTRAIT_DEFAULT, XTRAIT_NODEFAULT)(__VA_ARGS__)
#endif

#endif