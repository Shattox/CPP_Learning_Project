# Steve Chen

## TASK_0

### A - Execution

- c -> ajoute un nouvel avion.
- q ou x -> quitter le programme.
- f -> full screen.

- L'avion atteri, se gare et s'envole de nouveau.
  
- lift off -> l'avion s'envole.
- is now landing -> l'avion atteri.
- now servicing -> lorsque l'avion arrive au terminal.
- done servicing -> lorsque l'avion quite le terminal.


Lorsque l'on lance 4 avions, comme il n'y a que 
3 terminaux alors seulement 3 avions atteri et vont dans chacun des 3 terminaux.
L'autre avion continue de voler et atteri une fois qu'il y a une place de disponible.

### B - Analyse du code

- **AircraftType ->**
  Représente les caractéristiques d'un avion.
  Sa vitesse max au sol, en vol et l'accélération max.
  Stocke dans un tableau, les types des avions (Aircraft_type).


- **AirportType ->**
    Représente les différents types d'aéroport. Elle permet
    de gérer le décollage et l'atterissage des avions dans un
    aéroport et contient les positions des terminaux, pistes...


- **Runway ->**
    Représente une piste dans un aéroport.


- **TowerSimulation ->**
    Représente la classe principale de la simulation, elle gère
    la création des avions, les touches...


- **Waypoint ->**
    Représente l'état d'un avion si il est dans les airs ou bien
    au sol.


- **Point2D ->**
    Représente un point en 2D et contient les opérations
    arithmétiques de base.


- **Point3D ->**
    Représente un point en 3D et contient les opérations
    arithmétiques de base. 


- **Aircraft ->**
    Contient les informations sur les avions.
    Numéro de vol, vitesse, position, si il est dans le terminal,
    train d'aterrissage déployé.
    get_flight_num -> Renvoie le numéro du vol.
    - **distance_to ->** Renvoie la distance entre la position actuelle
       de l'avion d'une position p passé en paramètre.
    - **display ->** Dessine un avion sur l'écran.
    - **move ->** Gère le mouvement d'un avion en fonction de si il est dans
      les airs ou au sol.


- **Airport ->**
    Représente un aéroport, et de ce qu'elle est composé. 
    Elle permet de connaître l'état de celui-ci par exemple
    si un terminal est occupé ou non.
    - **get_tower ->** Renvoie la tour de l'aéroport.
    - **display ->** Dessine l'aéroport sur l'écran.
    - **move ->** Déplace les terminaux dans le vector de Terminal
      en appelant la fonction membre move du terminal.


- **Tower ->**
    Représente la tour d'un aéroport, elle gère tout ce qui est logistique.
    Par exemple les terminaux ou il y a déjà un avions.
    - **get_instructions ->** Réserve une place dans un terminal si il y en a 
      de libre, sinon il fait tourner l'avion en rond.
    - **arrived_at_terminal ->** Gère l'arrivé d'un avion dans un terminal.


- **Terminal ->**
    Représente l'état d'un terminal, si il est occupé ou non.
    - **in_use ->** Renvoie un booléan afin de savoir si le terminal est occupé.
    - **is_servicing ->** Renvoie vrai si le temrinal a finis de servir l'avion
      faux sinon.
    - **assign_craft ->** Assigne à la variable qui représente l'avion sur le
      terminal par l'avion passé en paramètre.
    - **start_service ->** Lorsque l'avion débarque au terminal, un message
      est envoyé et service_progress est remis à 0.
    - **finish_service ->** Lorsque l'avion quitte le terminal envoie un 
      message et la variable qui représente l'avion dans le terminal est
      mis à nullptr.
    - **move ->** Incrémente une variable qui gère le temps qu'un avion
      passe dans le terminal.


- Les classes et fonctions impliquées dans la génération du chemin d'un avion sont :
  - **Tower ->** **get_instructions** 
  - **WayPoint**
  - **AirportType**

Le conteneur choisi est une **deque**. L'intérêt de ce choix est que l'on peut
d'une part d'insérer ou supprimer en tête ou queue de manière rapide et ces
opérations n'invalident pas le déréférencement des autres éléments de la **deque**.
De plus contrairement à un **std::vector** l'extension d'une **deque** est moins
coûteuse que celle d'un **std::vector**.

### C - Bidouillons !

1. Les vitesses maximales et accélérations sont définis dans la classe **aircraft_types**.


2. Lorsque l'on essaye de mettre en pause le programme en manipulant le framerate,
   il s'arrête car dans la fonction **timer** dans le fichier **opengl_interface** on divise
   par la variable **ticks_per_sec** qui gère le framerate lorsque celle-ci vaut **0** on a donc
   une division par **0**.

3.
  ```cpp
  constexpr unsigned int SERVICE_CYCLES = 40u;
  ```

4. On pouvait penser à supprimer l'avion dans la fonction **move** de
   la classe **Aircraft**. Il n'est pas sûr de procéder au retrait dans
   cette fonction car la boucle dans la fonction **timer** ne le permet pas, il faut la changer en **itérateur**.
   On supprime donc dans la fonction **timer** dans le fichier
   **opengl_interface.cpp**. Pour transmettre l'information on modifie
   le type de retour de la fonction **move** pour renvoyer un **bool**
   pour savoir si on peut retirer l'avion.

5. Il n'est pas pertinent de faire la même pour un **DynamicObject** car
   dans notre programme les classes qui héritent de **DynamicObject** héritent
   aussi de **Displayable**.

### D - Théorie

1. Seule la classe **Tower** peut réserver un terminal à l'aéroport car
   elle stocke l'état des terminaux en fonction de si il y a un avion ou non.

2. On est pas passé par une référence car dans la fonction, on modifie la
   variable passé en paramètre.

## TASK_1

### Objectif 1 - Référencement des avions

### B - Déterminer le propriétaire de chaque avion

1. C'est la fonction **timer** qui est responsable de la destruction des avions du programme.


2. La **display_queue** et la **move_queue** contiennent une référence sur un avion qui va être
   détruit.


3. on parcours le conteneur **move_queue** via un **iterateur**, dans ce parcours pour le
   **display_queue** on apelle son destructeur et pour la **move_queue** on utilise la
   fonction **erase** pour l'avion que l'on souhaite détruire.


4. Il n'est pas judicieux d'appliquer la même chose pour **AircraftManager** car si non un avion
   devra dépendre de **AircraftManager** ce qui n'est pas optimale.

### Objectif 2 - Usine à avions

### A - Création d'une factory

Il faut initialiser **context_initializer** avant l'initialisation de la variable 
**aircraft_factory** pour s'assurer que le constrcuteur de **context_initializer** soit
appelé avant celui de **factory**.

### Objectif 4 - Templates

### Objectif 1 - Devant ou derrière ?

2. Pour que l'évaluation du flag se fasse à la compilation et non à l'éxecution,
   il faut utiliser le ```if constexpr```. Pour cela il faut changer la fonction 
   add_waypoint en une fonctions-template paramétré par un ```bool```.


### Choix d'implémentation

L'utilisation des containers appropriés tel que :
un set pour stocker les numéros des vols qui doivent être unique.
un vector pour stocker les avions afin de pouvoir utiliser les différentes
fonctions liées au vector pour trié, itéré... plus facilement.
Utiliser les fonctions déjà définis pour effectuer une action sur un container.

### Situation bloqué, solution trouvée

J'avais un problème lorsque j'ai du rajouter le aircraft_manager dans le constructeur
de Aiport. J'ai résolu le problème en appellant dans la fonction 
```void TowerSimulation::launch()``` ```init_aircraft_manager()``` avant ```init_airport```
Bloqué sur la Task 4 Objectif 2.

### Avis sur le projet

Projet très guidé qui nous fait utiliser les notions vu dans les différents chapitre.