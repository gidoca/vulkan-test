#ifndef VK_FUNCTION_POINTER_H
#define VK_FUNCTION_POINTER_H

#include <stdexcept>

#define VK_INSTANCE_FUNC(instance, name) VkInstanceFunctionPointer<PFN_##name> name{(instance), #name};

template<typename F>
struct ReturnType { };

template<typename R, typename... A>
struct ReturnType<R(A...)> { typedef R Type; };

template<typename R, typename... A>
struct ReturnType<R(*)(A...)> { typedef R Type; };

template<typename Function>
class VkInstanceFunctionPointer {
public:
	typedef typename ReturnType<Function>::Type RetType;

	VkInstanceFunctionPointer(VkInstance instance, const char* name) {
		func = (Function)vkGetInstanceProcAddr(instance, name);
		if (func == nullptr) {
			throw std::runtime_error(std::string("Could not find procedure address for ") + name);
		}
	}

	template<typename... A>
	RetType operator()(A... args) {
		return func(args...);
	}

private:
	Function func;
};

#endif