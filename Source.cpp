#include <iostream>
#include <vector>
#include <span>
#include <utility>   // pair
#include <algorithm> // minmax_element

// SOLUCIÓN MÁGICA:
// 1. Cambiamos el template para aceptar "Cualquier Contenedor" (Range)
// 2. Usamos 'auto' en el retorno para que C++ calcule el tipo (int, double, etc.) solo.
template <typename Container>
auto valorMinMax(const Container& input)
{
    // 3. AQUÍ DENTRO convertimos a span.
    // C++20 es listo y sabe crear un span desde un vector o array automáticamente aquí.
    std::span datos{ input };

    if (datos.empty()) {
        // Manejo de error simple: retornamos ceros del tipo que tenga el contenedor
        using T = typename decltype(datos)::value_type;
        return std::pair<T, T>{0, 0};
    }

    auto [itMin, itMax] = std::minmax_element(datos.begin(), datos.end());

    // Retornamos el par. Como la función es 'auto', deduce que es pair<int, int>
    return std::pair{ *itMin, *itMax };
}

int main()
{
    // CASO 1: Array estilo C
    int arr[5]{ 10, 5, 100, -3, 20 };

    // ¡FUNCIONA! Sin <int>, sin std::span{...}. Limpio.
    auto [min1, max1] = valorMinMax(arr);

    std::cout << "Array C  -> Min: " << min1 << ", Max: " << max1 << "\n";


    // CASO 1: Array estilo C
    double arrDouble[5]{ 10.4, 5.0, 100.0, -3.0, 20.0 };

    // ¡FUNCIONA! Sin <int>, sin std::span{...}. Limpio.
    auto [minD, maxD] = valorMinMax(arrDouble);

    std::cout << "Array C double  -> Min: " << minD << ", Max: " << maxD << "\n";

    


    // CASO 2: std::vector
    std::vector<double> v{ 3.14, 1.1, 9.9, 2.5 };

    // ¡FUNCIONA! Deduce automáticamente double
    auto [min2, max2] = valorMinMax(v);

    std::cout << "Vector   -> Min: " << min2 << ", Max: " << max2 << "\n";

    return 0;
}