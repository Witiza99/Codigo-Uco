from scipy.stats import wilcoxon
from scipy.stats import friedmanchisquare

tree_base = [77.22074468085107,94.57142857142857,91.08974358974359,93.0,59.142857142857146,91.19360902255639]
tree_ovo = [78.48847517730496,95.04761904761902,90.1923076923077,90.27272727272728,60.42857142857143,92.25250626566415]
tree_ova = [73.46631205673759,94.76190476190474,91.98717948717947,93.0,52.33333333333333,92.05513784461152]
tree_ecoc = [79.14007092198581,95.23809523809521,74.35897435897435,93.0,59.857142857142854,91.89849624060149]

stat, p2 = friedmanchisquare(tree_base,tree_ovo,tree_ova,tree_ecoc)
print("Statistics_Iman-Davenport=",stat,", ",p2)

w, p = wilcoxon(tree_base, tree_ovo)
print("Statistics_wilcoxon_tree_base_y_tree_ovo=", w,", ", p)

w, p = wilcoxon(tree_base, tree_ova)
print("Statistics_wilcoxon_tree_base_y_tree_ova=", w,", ", p)

w, p = wilcoxon(tree_base, tree_ecoc)
print("Statistics_wilcoxon_tree_base_y_tree_ecoc=", w,", ", p)
