#include <rapidjson/document.h>
#include <typeinfo>
#include <string>
namespace Resource
{
	static const std::string double_name_ = std::string(typeid(double).name());
	static const std::string float_name_ = std::string(typeid(float).name());
	static const std::string int_name_ = std::string(typeid(int).name());
	static const std::string bool_name_ = std::string(typeid(bool).name());
	static const std::string string_name_ = std::string(typeid(std::string).name());
	static const std::string uint_name_ = std::string(typeid(unsigned int).name());
	static const std::string uchar_name_ = std::string(typeid(unsigned char).name());
	template <class ValueClass>
	bool getJsonValue(std::string field_name,rapidjson::Value const& json, ValueClass& value)
	{
		bool ret = false;
		switch (json[field_name.c_str()].GetType())
		{
		case rapidjson::kNumberType:
		
			if (typeid(ValueClass).name() == double_name_ || typeid(ValueClass).name() == float_name_ || typeid(ValueClass).name() == int_name_|| typeid(ValueClass).name() == uint_name_ || typeid(ValueClass).name() == uchar_name_)
			{
				ret = true;
			}
			break;
		case rapidjson::kTrueType:
			if (typeid(ValueClass).name() == bool_name_)
			{
				ret = true;
			}
			break;
		case rapidjson::kFalseType:
			if (typeid(ValueClass).name() == bool_name_)
			{
				ret = true;
			}
			break;
		case rapidjson::kStringType:
			if (typeid(ValueClass).name() == string_name_)
			{
				ret = true;
			}
			break;
		default:
			break;
		}
		if (ret)
		{
			value = json[field_name.c_str()].Get<ValueClass>();
		}
		else
			std::cout << "Wrong format for field : " << field_name << ", can't covert to type : " << typeid(ValueClass).name() << std::endl;
		return ret;
	}

	template <>
	inline bool getJsonValue<unsigned char>(std::string field_name, rapidjson::Value const& json, unsigned char& value)
	{
		bool ret = false;
		if(json[field_name.c_str()].GetType()== rapidjson::kNumberType)
		{
			ret = true;
		}
		if (ret)
		{
			value = static_cast<unsigned char>(json[field_name.c_str()].GetUint());
		}
		else
			std::cout << "Wrong format for field : " << field_name << ", can't convert to type : " << typeid(unsigned char).name() << std::endl;
		return ret;
	}
}