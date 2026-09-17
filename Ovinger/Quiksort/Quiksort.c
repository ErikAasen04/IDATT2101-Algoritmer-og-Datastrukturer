#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Summerer alle tallene i tabellen. */
long long checksum(const int array[], int number)
{
    long long sum = 0;

    for (int i = 0; i < number; i++)
    {
        sum += array[i];
    }

    return sum;
}

/* Returnerer false dersom et tall er større enn det neste. */
bool is_sorted(const int array[], int number)
{
    for (int i = 0; i < number - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }

    return true;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Ordner første, midterste og siste verdi. */
int median3sort(int array[], int low, int high)
{
    int middle = low + (high - low) / 2;

    if (array[low] > array[middle])
    {
        swap(&array[low], &array[middle]);
    }

    if (array[middle] > array[high])
    {
        swap(&array[middle], &array[high]);

        if (array[low] > array[middle])
        {
            swap(&array[low], &array[middle]);
        }
    }

    return middle;
}

int partition(int array[], int low, int high)
{
    int middle = median3sort(array, low, high);
    int pivot = array[middle];

    swap(&array[middle], &array[high - 1]);

    int left = low;
    int right = high - 1;

    while (true)
    {
        while (array[++left] < pivot)
        {
        }

        while (array[--right] > pivot)
        {
        }

        if (left >= right)
        {
            break;
        }

        swap(&array[left], &array[right]);
    }

    swap(&array[left], &array[high - 1]);

    return left;
}

void quickSort(int array[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    if (high - low > 2)
    {
        int pivot_position = partition(array, low, high);

        quickSort(array, low, pivot_position - 1);
        quickSort(array, pivot_position + 1, high);
    }
    else
    {
        median3sort(array, low, high);
    }
}

void dualPivotQuickSort(int array[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int third = (high - low) / 3;

    swap(&array[low], &array[low + third]);
    swap(&array[high], &array[high - third]);

    if (array[low] > array[high])
    {
        swap(&array[low], &array[high]);
    }

    int p = array[low];
    int q = array[high];

    int left = low + 1;
    int right = high - 1;
    int current = left;

    while (current <= right)
    {
        if (array[current] < p)
        {
            swap(&array[current], &array[left]);
            left++;
        }
        else if (array[current] > q)
        {
            while (array[right] > q && current < right)
            {
                right--;
            }

            swap(&array[current], &array[right]);
            right--;

            if (array[current] < p)
            {
                swap(&array[current], &array[left]);
                left++;
            }
        }

        current++;
    }

    left--;
    right++;

    swap(&array[low], &array[left]);
    swap(&array[high], &array[right]);

    dualPivotQuickSort(array, low, left - 1);
    if (p < q)
    {
        dualPivotQuickSort(array, left + 1, right - 1);
    }

    dualPivotQuickSort(array, right + 1, high);
}

void fill_array(int array[], int number, int type)
{
    for (int i = 0; i < number; i++)
    {
        switch (type)
        {
        case 0:
            /* Kombiner to tilfeldige tall for større verdiområde. */
            array[i] = (rand() % 32768) * 32768
                + (rand() % 32768);
            break;

        case 1:
            /* Annenhvert element har samme verdi. */
            array[i] = (i % 2 == 0)
                ? 25
                : (rand() % 32768) * 32768
                + (rand() % 32768);
            break;

        case 2:
            array[i] = i;
            break;

        case 3:
            array[i] = number - i;
            break;
        }
    }
}

int main(void)
{
    const int number = 50000000;
    size_t bytes = (size_t)number * sizeof(int);

    int* original = malloc(bytes);
    int* single_array = malloc(bytes);
    int* dual_array = malloc(bytes);

    const char* data_names[] = {
        "Random numbers",
        "Many duplicates",
        "Already sorted",
        "Reverse sorted"
    };

  
    srand(time(NULL));

    for (int type = 0; type < 4; type++)
    {
        fill_array(original, number, type);

        /* Begge algoritmene får identiske startdata. */
        memcpy(single_array, original, bytes);
        memcpy(dual_array, original, bytes);

        long long sum_before = checksum(original, number);

        clock_t start_single = clock();
        quickSort(single_array, 0, number - 1);
        clock_t end_single = clock();

        clock_t start_dual = clock();
        dualPivotQuickSort(dual_array, 0, number - 1);
        clock_t end_dual = clock();

        double time_single =
            (double)(end_single - start_single) / CLOCKS_PER_SEC;

        double time_dual =
            (double)(end_dual - start_dual) / CLOCKS_PER_SEC;

        bool single_checksum_ok =
            checksum(single_array, number) == sum_before;
        bool single_sorted_ok =
            is_sorted(single_array, number);

        bool dual_checksum_ok =
            checksum(dual_array, number) == sum_before;
        bool dual_sorted_ok =
            is_sorted(dual_array, number);

        printf("\n--- %s: %d numbers ---\n", data_names[type], number);

        printf("Single-pivot total: %.6f seconds\n", time_single);
        printf("Checksum: %s | Same order: %s\n",
            single_checksum_ok ? "SUCCESS" : "FAILED",
            single_sorted_ok ? "SUCCESS" : "FAILED");

        printf("Dual-pivot totalt:   %.6f seconds\n", time_dual);
        printf("Checksum: %s | Same order: %s\n",
            dual_checksum_ok ? "SUCCESS" : "FAILED",
            dual_sorted_ok ? "SUCCESS" : "FAILED");
    }

    free(original);
    free(single_array);
    free(dual_array);

    return 0;
}