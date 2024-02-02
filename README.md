# C-est-pas-un-ton-camioneur (alias CY-Trucks)

L'executable qui fera tout les tris ce nome "marcel".
l'integralité du programe est compris dans le dossier CyTrucks. il n'y a pas de nécéssieter de télécharger autre chose.

Pour qu'il fonctionne corectement depuis n'importe quel dossier, executer la commande "export PATH=$PATH:$(pwd)" en etant situer dans le dossier CyTrucks. Placer ce dernier dans le dossier /home/bin devrai aussi fonctioner

l'éxecution du programe ce fait de cette magnère : "marcel [option] "fichier_a_traiter.csv"
assurer vous d'avoir un dossier ~/Image pour que le program deplace l'image (nomer Histograme.png) dans ce dernier. si le dossier n'existe pas, l'image sera par défaut dans le fichier ou vous vous trouver au moment d'executer la comande.

liste des option :

-d1 affiche les 10 conducteur ayant le plus de trajet dans l'ordre decroissant

-d2 affiche les 10 conducteur ayant parcourue la plus grande distance dans l'ordre decroissant

-l affiche les 10 trajet les plus long

-t affiche les 10 ville les plus traverser

-s affiche les 50 trajet avec le plus grand ecart entre leur distance maximal et minimal entre chaque étape
