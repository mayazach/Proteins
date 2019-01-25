Όνομα εκτελέσιμου προγράμματος: proteins

Για να μεταγλωττιστεί το πρόγραμμα, θα πρέπει στη γραμμή 15 του Makefile να μπει το path προς τη βιβλιοθήκη Eigen, που χρησιμοποιήται για τις συναρτήσεις υπολογισμού c-RMSD.

Έχει υλοποιηθεί το 1ο μέρος της εργασίας. Ακολουθούν οι τιμές που βρέθηκαν στο silhouette και για τις δυο συναρτήσεις απόστασης για διάφορες τιμές του k (χρησιμοποιώντας το bio_small_input.dat):

k	silhouette(frechet)	silhouette(crmsd)
3	0.173761			0.187833
4	0.19533				0.229192
5	0.172724			0.119973
6	0.255923			0.210991
7	0.203775			0.254961
8	0.206479			0.237389
9	0.296993			0.263577
10	0.270757			0.187496
11	0.267104			0.248348
12	0.222081			0.228222
13      0.27426 			0.303223
14      0.272999			0.287927
16      0.362732			0.27834
17      0.281251			0.324038
18      0.334916			0.298444
20      0.340437			0.285346

Σταματήσαμε τις δοκιμές μετά το 20 γιατί είχαν αρχίσει κάποια clusters να βγαίνουν άδεια. Από αυτά τα αποτελέσματα, φαίνεται αισθητή βελτίωση του silhouette από 6 clusters και πάνω.

Καλύτερη τιμή k για την c-RMSD: 17
Καλύτερη τιμή k για την Discrete Frechet: 16 


Το πρόγραμμα περιλαμβάνει τα παρακάτω αρχεία:
-main.cpp: διάβασμα αρχείου εισόδου, αποθήκευση καμπυλών, κατασκευή δομών, εκτέλεση του αλγοριθμου kmeans με το συνδυασμό συναρτήσεων random selection-Lloyd's assignment-PAM για τις συναρτήσεις απόστασης c-RMSD και Discrete Frechet, και καταγραφή αποτελεσμάτων στα αρχεία εξόδου.
-curve.h: αντικείμενο της καμπύλης, με τα σημεία και το id της, καθώς και αν ανήκει στο dataset, αν ανήκει σε cluster  το id του αν ναι (για τη συνάρτηση lsh)
-curveList.h,curveList.cpp: λίστα καμπυλών
-hash.h,hash.cpp: πίνακας κατακερματισμού για καμπύλες
-gridcurves.h,gridcurves.cpp: συνάρτηση απεικόνισης καμπύλης σε καμπύλες πλέγματος
-distance.h,distance.cpp: Discrete Frechet Distance, Dynamic Time Warping
-randomnum.h,randomnum.cpp: γεννήτριες τυχαίων αριθμών, με κανονική και ομοιόμορφη κατανομή, και αριθμών Marsaglia
-cluster.h, cluster.cpp: αντικείμενο του cluster με το id, το κέντρο και δείκτες στα σημεία του
-kfunctions.h, kfunctions.cpp: συναρτήσεις random αρχικοποίησης, Lloyd και LSH ανάθεσης και PAM update
-dfd_res.h:struct με τις απαραίτητες πληροφορίες για τον υπολογισμό της Mean Discrete Frechet Curve
-optimal_traversal.h, optimal_traversal.cpp:υπολογισμός της Mean Discrete Frechet Curve
-pairsList.h, pairsList.cpp:λίστα με ζεύγη σημείων για τον υπολογισμό της Mean Discrete Frechet Curve
-binaryTree.h, binaryTree.cpp: δυαδικό δέντρο καμπύλων για υπολογισμό του Mean Discrete Frechet
-kmeans_initialization.h, kmeans_initialization.cpp:επιλογή αρχικών κέντρων με εφαρμογή του αλγορίθμου k-means++
-silhouette.h, silhouette.cpp: υπολογισμός αριθμών silhouette για την DFT
-crmsd.h, crmsd.cpp:υλοποίηση των αλγορίθμων για τον υπολογισμό της c-RMSD και της Discrete Frechet distance με χρήση της βιβλιοθήκης Eigen
