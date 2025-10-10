import random
import time

def bubble_sort(arr):
    a = arr.copy()
    n = len(a)
    swaps = 0
    start = time.time()
    for i in range(n):
        for j in range(0, n - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swaps += 1
    end = time.time()
    return a, end - start, swaps


def insertion_sort(arr):
    a = arr.copy()
    swaps = 0
    start = time.time()
    for i in range(1, len(a)):
        key = a[i]
        j = i - 1
        while j >= 0 and a[j] > key:
            a[j + 1] = a[j]
            j -= 1
            swaps += 1
        a[j + 1] = key
    end = time.time()
    return a, end - start, swaps


def selection_sort(arr):
    a = arr.copy()
    swaps = 0
    start = time.time()
    for i in range(len(a)):
        min_idx = i
        for j in range(i + 1, len(a)):
            if a[j] < a[min_idx]:
                min_idx = j
        if min_idx != i:
            a[i], a[min_idx] = a[min_idx], a[i]
            swaps += 1
    end = time.time()
    return a, end - start, swaps


def quick_sort(arr):
    a = arr.copy()
    swaps = [0]

    def _quick_sort(a):
        if len(a) <= 1:
            return a
        pivot = a[len(a) // 2]
        left = [x for x in a if x < pivot]
        middle = [x for x in a if x == pivot]
        right = [x for x in a if x > pivot]
        swaps[0] += len(left) + len(right)
        return _quick_sort(left) + middle + _quick_sort(right)

    start = time.time()
    result = _quick_sort(a)
    end = time.time()
    return result, end - start, swaps[0]


def merge_sort(arr):
    a = arr.copy()
    swaps = [0]

    def _merge_sort(a):
        if len(a) > 1:
            mid = len(a) // 2
            L = a[:mid]
            R = a[mid:]
            _merge_sort(L)
            _merge_sort(R)
            i = j = k = 0
            while i < len(L) and j < len(R):
                if L[i] < R[j]:
                    a[k] = L[i]
                    i += 1
                else:
                    a[k] = R[j]
                    j += 1
                swaps[0] += 1
                k += 1
            while i < len(L):
                a[k] = L[i]
                i += 1
                k += 1
            while j < len(R):
                a[k] = R[j]
                j += 1
                k += 1

    start = time.time()
    _merge_sort(a)
    end = time.time()
    return a, end - start, swaps[0]


def shaker_sort(arr):
    a = arr.copy()
    swaps = 0
    start = time.time()
    left = 0
    right = len(a) - 1
    while left <= right:
        for i in range(left, right):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
                swaps += 1
        right -= 1
        for i in range(right, left, -1):
            if a[i - 1] > a[i]:
                a[i], a[i - 1] = a[i - 1], a[i]
                swaps += 1
        left += 1
    end = time.time()
    return a, end - start, swaps


def test_sorts():
    sizes = [1000, 10000, 100000]
    algorithms = [
        ("Bubble", bubble_sort),
        ("Insertion", insertion_sort),
        ("Selection", selection_sort),
        ("Quick", quick_sort),
        ("Merge", merge_sort),
        ("Shaker", shaker_sort)
    ]

    for n in sizes:
        print(f"\nРазмер массива: {n}")
        base = [random.randint(0, 100000) for _ in range(n)]
        for name, func in algorithms:
            best_time = float('inf')
            best_swaps = 0
            for _ in range(5):
                _, t, s = func(base)
                if t < best_time:
                    best_time = t
                    best_swaps = s
            print(f"{name:10s} | Время: {best_time:.4f} c | Перестановок: {best_swaps}")

test_sorts()
