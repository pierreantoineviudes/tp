"""Python implementation of merge sort

Returns:
    _type_: _description_
"""

import numpy as np


def tri(tab: list) -> list:
    """_summary_

    Args:
        tab (list): unsorted array

    Returns:
        list: sorted array
    """
    if len(tab) <= 1:
        return tab
    tab_1 = tab[: len(tab) // 2]
    tab_2 = tab[len(tab) // 2 :]
    tab_1 = tri(tab_1)
    tab_2 = tri(tab_2)
    return fusion(tab_1, tab_2, tab)


def fusion(tab_1: list, tab_2: list, tab: list) -> list:
    """merge the sorted sub_arrays

    Args:
        tab_1 (list): sorted sub_sub_array1
        tab_2 (list): sorted_sub_sub_array2
        tab (list): sub_array to sort

    Returns:
        list: sorted sub_array
    """
    ind_1, ind_2, ind = 0, 0, 0
    while tab_1 and tab_2 and ind_1 < len(tab_1) and ind_2 < len(tab_2):
        if tab_1[ind_1] < tab_2[ind_2]:
            tab[ind] = tab_1[ind_1]
            ind += 1
            ind_1 += 1
        else:
            tab[ind] = tab_2[ind_2]
            ind += 1
            ind_2 += 1

    # empty the lasting numbers in tab_1 and tab_2
    while tab_1 and ind_1 < len(tab_1):
        tab[ind] = tab_1[ind_1]
        ind += 1
        ind_1 += 1
    while tab_2 and ind_2 < len(tab_2):
        tab[ind] = tab_2[ind_2]
        ind += 1
        ind_2 += 1
    return tab


if __name__ == "__main__":
    tab = np.random.randint(0, 100, 10).tolist()
    print("tab _raw : ", tab)
    tab = tri(tab)
    print("tab sorted : ", tab)
