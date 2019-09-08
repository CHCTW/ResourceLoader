#include <magic_enum.hpp>
#include <typeinfo>
#include <iostream>
namespace Resource
{
	template<class ValueClass, class EnumClass>
	inline bool convertEnum(ValueClass&& value, EnumClass&& result)
	{
		auto temp = magic_enum::enum_cast<EnumClass>(value);
		if (temp.has_value())
		{
			result = temp.value();
			return true;
		}
		std::cout << "Can't covert " << value <<"("<<typeid(ValueClass).name() <<") to " << typeid(EnumClass).name() << std::endl;
		return false;
	}
}