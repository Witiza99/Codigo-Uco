from scipy.stats import wilcoxon
from scipy.stats import friedmanchisquare
#from scipy.stats import imanDavenportTest

vtree = [94.70967741935483, 76.59574468085107, 94.76190476190474, 90.32051282051282, 83.28333333333333, 93.0, 68.92732354996505, 61.19047619047618, 81.66666666666666, 92.06140350877193]
vSVM = [96.18320610687023, 92.19512195121952, 97.55555555555556, 96.29629629629629, 88.67924528301887, 100.0, 79.22077922077922, 63.07692307692307, 88.88888888888889, 93.4156378600823]
vKvecinos = [92.36641221374046, 88.29268292682927, 95.11111111111111, 74.07407407407408, 86.79245283018868, 97.77777777777777, 77.05627705627705, 64.61538461538461, 100.0, 93.00411522633745]
vtree_conf1 = [93.54838709677419]
vtree_conf2 = [100.0]
vtree_conf3 = [93.54838709677419]
vtree_conf4 = [96.7741935483871]
vtree_conf5 = [93.33333333333333]
vtree_conf6 = [93.33333333333333]
vtree_conf7 = [96.66666666666667]
vtree_conf8 = [96.66666666666667]
vtree_conf9 = [96.66666666666667]
vtree_conf10 = [90.0]
vSVM_conf1 = [93.54838709677419]
vSVM_conf2 = [100.0]
vSVM_conf3 = [96.7741935483871]
vSVM_conf4 = [100.0]
vSVM_conf5 = [96.66666666666667]
vSVM_conf6 = [93.33333333333333]
vSVM_conf7 = [90.0]
vSVM_conf8 = [100.0]
vSVM_conf9 = [96.66666666666667]
vSVM_conf10 = [90.0]
vKvecinos_conf1 = [90.32258064516128]
vKvecinos_conf2 = [100.0]
vKvecinos_conf3 = [100.0]
vKvecinos_conf4 = [96.7741935483871]
vKvecinos_conf5 = [93.33333333333333]
vKvecinos_conf6 = [90.0]
vKvecinos_conf7 = [83.33333333333334]
vKvecinos_conf8 = [93.33333333333333]
vKvecinos_conf9 = [93.33333333333333]
vKvecinos_conf10 = [86.66666666666667]
w, p = wilcoxon(vSVM, vKvecinos)
print("Statistics_wilcoxon=", w,", ", p)

stat, p2 = friedmanchisquare(vtree_conf1,vtree_conf2,vtree_conf3,vtree_conf4,vtree_conf5,vtree_conf6,vtree_conf7,vtree_conf8,vtree_conf9,vtree_conf10)
print("Statistics_friedman_vtree=",stat,", ",p2)
stat, p2 = friedmanchisquare(vSVM_conf1,vSVM_conf2,vSVM_conf3,vSVM_conf4,vSVM_conf5,vSVM_conf6,vSVM_conf7,vSVM_conf8,vSVM_conf9,vSVM_conf10)
print("Statistics_friedman_vSVM=",stat,", ",p2)
stat, p2 = friedmanchisquare(vKvecinos_conf1,vKvecinos_conf2,vKvecinos_conf3,vKvecinos_conf4,vKvecinos_conf5,vKvecinos_conf6,vKvecinos_conf7,vKvecinos_conf8,vKvecinos_conf9,vKvecinos_conf10)
print("Statistics_friedman_vKvecinos=", stat,", ",p2)

stat2, p3 =friedmanchisquare(vtree, vSVM, vKvecinos)
print("Statistics_Iman-Davenport=", stat2,", ", p3)




	
