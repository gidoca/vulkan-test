#pragma once

#define VK_INSTANCE_FUNC(instance, name) VkInstanceFunctionPointer<PFN_##name> name{(instance), #name};

template <class R, class... A>
struct return_type<R(*)(A...)>
{
	typedef R type;
};

template<Function>
class VkInstanceFunctionPointer {
public:
	VkInstanceFunctionPointer(VkInstance instance, const char* name) {
		func = (Function)vkGetInstanceProcAddr(instance, name);
		if (func == nullptr) {
			throw std::runtime_exception
		}
	}

	template<typename... A>
	return_type<Function>::type operator()(A... args) {
		return func(args);
	}

private:
	Function func;
};