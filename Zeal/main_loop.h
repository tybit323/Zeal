#pragma once
#include "hook_wrapper.h"
#include "memory.h"
#include <functional>
#include <unordered_map>
enum class callback_fn
{
	MainLoop,
	Zone
};
class MainLoop
{
public:
	void do_callbacks(callback_fn fn);
	void add_callback(std::function<void()> callback_function, callback_fn fn = callback_fn::MainLoop);
	MainLoop(class ZealService* zeal);
	~MainLoop();
private:
	std::vector<std::function<void()>> callback_functions;
	std::vector<std::function<void()>> callback_functions_zone;
};

