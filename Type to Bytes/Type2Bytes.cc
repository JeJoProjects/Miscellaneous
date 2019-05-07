/* Refferences:
 * https://stackoverflow.com/questions/3991478/building-a-32-bit-float-out-of-its-4-composite-bytes
 * https://stackoverflow.com/questions/25386503/convert-a-float-to-4-uint8-t
 * https://stackoverflow.com/questions/21005845/how-to-get-float-in-bytes
 */

#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cstring>
#include <iomanip>

/* value2Bytes: converts values (of type bool, int and float) to
 * array of uint8_t which has array size = sizeof(type).
 */
template<typename ValueType, std::size_t N>
constexpr void value2Bytes(
	const ValueType value, uint8_t(&bytesArr)[N]) noexcept
{
	std::memcpy(bytesArr, &value, sizeof(bytesArr));
}
/* bytes2Value: returns the values (of type bool, int and float),
 * after converting the array of uint8_t(which has array size = sizeof(type))
 * to corresponding values.
 */
template<typename ValueType, std::size_t N>
constexpr ValueType bytes2Value(
	ValueType value, const uint8_t(&bytesArr)[N]) noexcept
{
	std::memcpy(&value, bytesArr, sizeof(value));
	return value;
}

template<typename Type>
constexpr void castFunction(const Type value) noexcept
{
	std::cout << "Currently type casting for: " << typeid(Type).name() << '\n';

	// from value to bytes array
	std::is_floating_point_v<Type> ?
		std::cout << "Before conversion... value = " << std::fixed << std::setprecision(4) << value << std::endl << std::endl :
		std::cout << "Before conversion... value = " << value << '\n';
	uint8_t  bytes[sizeof(Type)]{ '0' };
	value2Bytes<Type>(value, bytes);

	// from bytes array to value
	const auto reValue = bytes2Value<Type>(value, bytes);
	std::is_floating_point_v<Type> ?
		std::cout << "After conversion... value = " << std::fixed << std::setprecision(4) << reValue << std::endl << std::endl :
		std::cout << "After conversion... value = " << reValue << std::endl << std::endl;

}

int main()
{
	constexpr int bVal{ 1 };
	constexpr int iVal{ std::numeric_limits<int>::max() };
	constexpr double dVal{ 123489.08123f };

	castFunction<bool>(bVal ? true : false);
	castFunction<int>(iVal);
	castFunction<float>(static_cast<float>(dVal));

	return 0;
}

#if 0 // extras
float f = 0.1;
unsigned char* pc;
pc = (unsigned char*)& f;

// 0.6 in float
pc[0] = 0x9A;
pc[1] = 0x99;
pc[2] = 0x19;
pc[3] = 0x3F;

std::cout << f << std::endl;

*(unsigned int*)& f = (0x3F << 24) | (0x19 << 16) | (0x99 << 8) | (0x9A << 0);
#endif
