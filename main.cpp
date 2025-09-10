#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void arr_print_rectangle(int* data, size_t sizeY, size_t sizeX);
void arr_print_triangle(int* data, size_t sizeY);

int* triangle_allocate(size_t lines);
size_t triangle_amount_of_elements(size_t triangle_size);

int* my_address_function_rectangle(int* data, size_t sizeY, size_t sizeX, size_t y, size_t x);
int* my_address_function_triangle(int* data, size_t sizeY, size_t y, size_t x);

int search_max_triangle(int* data, size_t sizeY);
//int search_max_rectangle(int* data);

int search_min_triangle(int* data, size_t sizeY);
//int search_min_rectangle(int* data);

int main()
{
/*
    int my_data[][3] = {{10, 11, 12}, {20, 21, 22}, {30, 31, 32}, {40, 41, 42}};
    arr_print(&my_data[0][0], 4, 3);
*/

    size_t triangle_size = 5;

    int* ptr_first_triangle = triangle_allocate(triangle_size);
    for (size_t i = 0; i < triangle_amount_of_elements(triangle_size); i++)
        ptr_first_triangle[i] = i;

    int max_value = search_max_triangle(ptr_first_triangle, triangle_size);
    printf("%d\n", max_value);

    int min_value = search_min_triangle(ptr_first_triangle, triangle_size);
    printf("%d\n", min_value);

    arr_print_triangle(ptr_first_triangle, triangle_size);

    return 0;
}


void arr_print_rectangle(int* data, size_t sizeY, size_t sizeX)
{
    for (size_t y = 0; y < sizeY; y++)
    {
        for (size_t x = 0; x < sizeX; x++)
        {
            printf("[%lu][%lu] = %d ", y, x, *my_address_function_rectangle(data, sizeY, sizeX, y, x));
            printf("\n");
        }
    }
    printf("\n");
}

void arr_print_triangle(int* data, size_t sizeY) //sizeY = sizeX, поэтому оставляем только один
{
    for (size_t y = 0; y < sizeY; y++)
    {
        printf("\n");
        for (size_t x = 0; x <= y; x++)
            printf("[%lu][%lu] = %d ", y, x, *my_address_function_triangle(data, sizeY, y, x));
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

int* my_address_function_triangle(int* data, size_t sizeY, size_t y, size_t x) //нужен sizeY для ассертов
{
    assert(x <= y);
    assert(y <= sizeY); //< или <=?

    return (int*) ((size_t) data + ((y + 1) * (y + 2) / 2 - y - 1 + x) * sizeof(int));
}


size_t triangle_amount_of_elements(size_t triangle_size)
{
    return (triangle_size * (triangle_size + 1) / 2);
}


int search_max_triangle(int* data, size_t sizeY)
{
    assert(data != NULL);

    int max_value = -32768;

    for (size_t y = 0; y < sizeY; y++)
    {
        for (size_t x = 0; x <= y; x++)  //тут sizeY, так как sizeY = sizeX
        {
            int tmp = *my_address_function_triangle(data, sizeY, y, x);
            if (tmp > max_value)
                max_value = tmp;
        }
    }
    return max_value;
}

int search_min_triangle(int* data, size_t sizeY)
{
    assert(data != NULL);

    int min_value = 32767;

    for (size_t y = 0; y < sizeY; y++)
    {
        for (size_t x = 0; x <= y; x++)  //тут sizeY, так как sizeY = sizeX
        {
            int tmp = *my_address_function_triangle(data, sizeY, y, x);
            if (tmp < min_value)
                min_value = tmp;
        }
    }
    return min_value;
}
