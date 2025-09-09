#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void arr_print_rectangle(int* data, size_t sizeY, size_t sizeX);
void arr_print_triangle(int* data, size_t sizeY, size_t sizeX);

int* triangle_allocate(size_t lines);

int* my_address_function_rectangle(int* data, size_t sizeY, size_t sizeX, size_t y, size_t x);
int* my_address_function_triangle(int* data, size_t sizeY, size_t sizeX, size_t y, size_t x);

int main()
{
/*
    int my_data[][3] = {{10, 11, 12}, {20, 21, 22}, {30, 31, 32}, {40, 41, 42}};
    arr_print(&my_data[0][0], 4, 3);
*/

    int* ptr_first_triangle = triangle_allocate(5);
    for (int i = 0; i < 15; i++)
        ptr_first_triangle[i] = i;

    arr_print_triangle(ptr_first_triangle, 5, 5);

    return 0;
}


void arr_print_rectangle(int* data, size_t sizeY, size_t sizeX)
{
    for (size_t y = 0; y < sizeY; y++)
    {
        printf("\n");
        for (size_t x = 0; x < sizeX; x++)
            printf("[%lu][%lu] = %d ", y, x, *my_address_function_rectangle(data, sizeY, sizeX, y, x));
    }
    printf("\n");
}

void arr_print_triangle(int* data, size_t sizeY, size_t sizeX)
{
    for (size_t y = 0; y < sizeY; y++)
    {
        printf("\n");
        for (size_t x = 0; x <= y; x++)
            printf("[%lu][%lu] = %d ", y, x, *my_address_function_triangle(data, sizeY, sizeX, y, x));
    }
    printf("\n");
}

int* triangle_allocate(size_t lines)
{
    size_t amount_of_bytes = ((1 + lines) * lines) / 2;

    return (int*) calloc(amount_of_bytes, sizeof(int));
}

int* my_address_function_rectangle(int* data, size_t sizeY, size_t sizeX, size_t y, size_t x)
{
    return (int*) ((size_t) data + (y * sizeX + x) * sizeof(int));
}

int* my_address_function_triangle(int* data, size_t sizeY, size_t sizeX, size_t y, size_t x)
{
    assert(x <= y);

    return (int*) ((size_t) data + ((y + 1) * (y + 2) / 2 - y - 1 + x) * sizeof(int));
}
