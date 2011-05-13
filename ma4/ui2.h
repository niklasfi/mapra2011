#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <sstream>

namespace ui2{
	template <class T> std::function<bool(const T&)> check_true();
	template <class T> std::function<bool(const T&)> check_range(const T& l, const T& u);
	template <class T> std::function<bool(const T&)> check_larger(const T& lbound);
	template <class T> std::function<bool(const T&)> check_smaller(const T& lbound);
	
	template <class T> T readarg(std::string arg, std::string failmsg, std::function<bool(const T&)> chkfnc = ui2::check_true<T>());
};
