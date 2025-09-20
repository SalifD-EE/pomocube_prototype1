<a id="readme-top"></a>

[English](README.md) | **Français**

<div align="center">
  <h1 align="center">Projet Pomocube - Prototype 1</h1>
  <p align="center">
    Un minuteur pomodoro simple et direct &middot; Cliquez sur l'image ci-dessous pour voir une démo !
    <br />
  </p>

  [![Regarder la vidéo](https://img.youtube.com/vi/l40GzJ1xq9o/0.jpg)](https://www.youtube.com/watch?v=l40GzJ1xq9o)
</div>
  

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table des matières</summary>
  <ol>
    <li>
      <a href="#à-propos-du-projet">À propos du projet</a>
      <ul>
        <li><a href="#introduction">Introduction</a></li>
        <li><a href="#quest-ce-quun-pomodoro">Qu'est-ce qu'un pomodoro ?</a></li>
      </ul>
    </li>
    <li>
      <a href="#sélection-des-composants">Sélection des composants</a>
      <ul>
        <li><a href="#nomenclature">Nomenclature</a></li>
        <li><a href="#microcontrôleur">Microcontrôleur</a></li>
        <li><a href="#écran">Écran</a></li>
        <li><a href="#encodeur-rotatif">Encodeur rotatif</a></li>
        <li><a href="#buzzer-passif">Buzzer passif</a></li>
        <li><a href="#schéma-de-câblage">Schéma de câblage</a></li>
      </ul>
    </li>
    <li>
      <a href="#le-processus">Le processus</a>
      <ul>
        <li><a href="#faire-fonctionner-lencodeur">Faire fonctionner l'encodeur</a></li>
        <li><a href="#afficher-un-minuteur">Afficher un minuteur</a></li>
        <li><a href="#créer-une-machine-à-états">Créer une machine à états finis (FSM)</a></li>
        <li><a href="#implémenter-une-fonction-pause">Implémenter une fonction pause</a></li>
        <li><a href="#créer-un-menu-principal">Créer un menu principal</a></li>
        <li><a href="#implémenter-un-buzzer">Implémenter un buzzer</a></li>
        <li><a href="#assembler-le-tout">Assembler le tout</a></li>
      </ul>
    </li>
    <li><a href="#résultat-final">Résultat final</a></li>
    <li><a href="#conclusion">Conclusion</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#remerciements">Remerciements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
<a id="à-propos-du-projet"></a>
## À propos du projet

<a id="introduction"></a>
### Introduction

En tant qu'étudiant en génie électrique, je suis bien conscient que simplement obtenir le diplôme ne suffit pas pour se démarquer lors de la recherche d'emploi ou de stage, surtout dans le marché du travail actuel.
Une stratégie populaire pour contrer cela consiste à travailler sur des projets personnels pendant son temps libre. Par contre, étant un ingénieur, j'ai décidé d'en profiter pour résoudre un problème dans ma vie courante. Je vous présente donc le Pomocube.

<a id="quest-ce-quun-pomodoro"></a>
### Un pomodoro? C'est quoi ça?

Nommée d'après la minuterie de cuisine en forme de tomate, la technique pomodoro est une façon de rester concentré pendant de longues périodes de temps. Un cycle typique implique 25 minutes de travail suivi de 5 minutes de pause. On répète ensuite ce cycle 3 fois de plus, avec une pause plus longue à la fin. Les pauses régulières permettent de rester attentif, et le résultat est une productivité accrue. De plus, la prochain petite récompense n'est jamais très loin. Tout le monde est différent, mais j'ai personnellement eu beaucoup de succès avec cette technique pour étudier et travailler.

Bien sûr, il existe déjà beaucoup d'applications pomodoro, et j'en ai utilisé plusieurs au fil des années (d'ailleurs, ma préférée est [Flow](https://www.flow.app/)).
Ceci étant dit, vous vous demandez peut-être pourquoi j'entreprends ce projet. Voici quelques raisons :

* J'ai besoin d'un projet personnel, et celui-ci offre un équilibre parfait entre simplicité, pertinence et utilité.
* Les applications pomodoro sur Windows et MacOS prennent de la place sur l'écran et ne se synchronisent parfois pas entre les plateformes.
* Les applications mobiles consomment de l'énergie et nécessitent un support pour tenir le téléphone en place.
* Peu importe l'appareil utilisé, je suis forcé de télécharger <em>une autre app</em>, et j'en ai RAS-LE-BOL des apps.

C'est là que j'ai eu l'idée de créer un petit minuteur qui est élégant, agréable à utiliser et facile à transporter.
Le but de ce gadget est d'être simple et à fonctionnalité unique, une petite pause de tous ces appareils hyper-connectés qui .
Voici une image 3D du design que j'ai en tête pour la version finale :
<br/>
<div align="center">
  <img width="40%" height="40%" alt="rendu pomocube" src="https://github.com/user-attachments/assets/b528b48f-cb07-4bba-9183-2ecd1d8c3783" />
</div>
<br/>

L'ingénierie et l'apprentissage sont toutes deux des tâches de longue haleine. J'ai donc choisi de travailler par itérations plutôt que d'essayer d'atteindre ce résultat final dès le départ. Ce premier prototype vise à
implémenter quelques fonctionnalités de base. Les révisions ultérieures utiliseront des pièces différentes ainsi que des fonctionnalités plus sophistiquées.


<!-- PARTS SELECTION -->
<a id="sélection-des-composants"></a>
## Sélection des composants

Continuant sur le thème de la simplicité, ce projet nécessite très peu de composants pour fonctionner.

<a id="nomenclature"></a>
### Nomenclature

| Description | Numéro de pièce | Quantité | Coût unitaire (CAD) |
|---|---|---|---|
| ELEGOO Arduino Uno R3 avec ATmega328P | EL-CB-001 | 1 | 24,99 $ |
| GeeekPi 0.96" OLED Monochrome | - | 1 | 4,80 $ |
| Cylewet KY-40 Encodeur rotatif | CLT1062 | 1 | 2,80 $ |
| Buzzer passif | - | 1 | 0,88 $ |
| Total | - | - | 33,47 $ |

<a id="microcontrôleur"></a>
### Microcontrôleur - ATmega328P (avec Arduino Uno R3)

Oui, j'utilise un Arduino, mais laissez-moi m'expliquer. La vérité est que je n'étais pas conscient de la réputation de cette plateforme quand j'ai commencé à jouer avec les systèmes embarqués.
Au moment où j'ai appris que ce MCU est très vieux et que la plateforme Arduino simplifie beaucoup de choses, j'avais déjà acheté de l'équipement,
alors j'ai décidé de faire un prototype rapide avec ce que j'avais pour m'initier aux bases et avoir quelque chose à montrer à la journée stages et emplois de mon école,
qui a lieu dans 2 semaines au moment où j'écris ces lignes. L'intention n'a jamais été de faire la version finale avec ce MCU ou avec l'IDE Arduino.
Je prévois utiliser le STM32-F446RE, qui est beaucoup plus puissant à la place. Pour cette première itération cependant, cela fera l'affaire.

<a id="écran"></a>
### Écran - 0.96" SSD1306 OLED Monochrome

Cet écran est super économique, a beaucoup de support et de documentation, et l'affichage est très clair. Mon interface utilisateur contient beaucoup d'espace vide, ce qui se marie bien
avec les noirs profonds pour lesquels les OLED sont connus. Ce projet est assez simple pour ne pas nécessiter de communication haute vitesse, donc la configuration à 2 câbles du protocole I²C
aide également à désencombrer le câblage.

<a id="encodeur-rotatif"></a>
### Encodeur rotatif - KY-40

Cet encodeur rotatif est la seule forme d'entrée pour cet appareil. Il est satisfaisant à faire tourner et assez intuitif.
Le bonus supplémentaire du KY-40 est qu'il est soudé à un PCB qui inclut déjà les résistances dont j'ai besoin pour filtrer
le bruit des signaux SW, CLK et DT. Cela le rend un peu plus difficile à garder en place sur un breadboard, mais je peux m'arranger.

<a id="buzzer-passif"></a>
### Buzzer passif

C'est celui qui est venu avec mon kit de démarrage Arduino. Il fait son travail.

<a id="schéma-de-câblage"></a>
### Schéma de câblage

<div align="center">
  <img width="40%" height="40%" alt="{C89FDA2B-B4BD-4FD9-9956-544990561FB0}" src="https://github.com/user-attachments/assets/bffef6d4-cfb3-4b5c-992a-340779c5e63c" />
</div>

<!-- THE PROCESS -->
<a id="le-processus"></a>
## Le processus

### Configurer l'encodeur
<a id="faire-fonctionner-lencodeur"></a>
J'ai commencé par tester l'encodeur rotatif. C'est assez simple de le faire
fonctionner avec l'Uno R3. Le seul petit problème que j'ai rencontré est que mon encodeur avait ses capteurs DT et CLK inversés par rapport au tutoriel que je suivais,
ce qui l'amenait à lire les directions de manière inversée (horaire était détecté comme antihoraire et vice versa). C'est une bonne chose parce que cela m'a forcé à comprendre
comment l'appareil fonctionne réellement. La solution était simplement d'inverser la logique dans le code de DT != CLK à DT == CLK.

<div align="center">
  <img width="371" height="441" alt="image" src="https://github.com/user-attachments/assets/f5e2d0a1-2fed-4f4c-a66a-c00109776211" />
</div>

<a id="afficher-un-minuteur"></a>
### Afficher un minuteur
Maintenant que l'encodeur est fonctionnel, ma tâche suivante était de faire fonctionner l'écran OLED. D'abord, j'ai dû choisir entre utiliser une librairie, suivre un tutoriel, ou écrire la logique moi-même.
J'ai opté pour la librairie Adafruit GFX pour gérer l'affichage des pixels, et je me suis occupé de la logique de la minuterie moi-même.

J'ai utilisé la fonction millis() d'Arduino comme base. Cette dernière compte combien de temps en millisecondes s'est écoulé depuis le démarrage du MCU. Ma logique est principalement centrée autour de
l'enregistrement de la valeur de millis() quand la minuterie démarre.

```
elapsedTime = millis() - timerStartTime;
```

Un petit défi était d'afficher un zéro avant le chiffre quand il y a moins de 10 secondes dans un segment de l'écran.
Il suffit d'ajouter un zéro si la section est moins élevé que 10.

```
if (minDisplay < 10) display.print("0");
display.print(minDisplay);
```

Le prochain défi était de gérer la fin d'un segment. Au début, je pensais que j'avais juste besoin de vérifier si le temps restant était supérieur à zéro.
Mais le résultat était qu'en fin de session la durée passait soudainement de quelques secondes à plus de 50 min. Pourquoi ? J'ai affiché le temps restant sur le Serial Monitor pour comprendre ce qui se passait (l'Uno ne supporte pas le débogage, hélas).

```
195
150
105
61
16
4294967268
4294967223
4294967179
4294967135
```

C'est là que j'ai compris. Un vérification approfondie révèle que la minuterie interne de l'ATmega 328P est mise à jour environ chaque 45 ms à 16 MHz, donc si le temps restant était plus petit que ce tick, nous irions dans les négatifs, sauf qu'il n'y a <em>pas</em> de négatifs dans le contexte actuel, parce que le temps est géré avec des unsigned longs. Cela cause un débordement à la valeur la plus élevée possible pour ce type de variable, qui est environ 4,29 milliards. C'est pour cela que dans la sortie ci-haut, nous passons de 16 à des nombres énormes.
La solution était de mettre à jour la minuterie seulement si le temps restant était à plus d'un tick de zéro, sinon, le segment est terminé, et la minuterie s'arrête. Il y a une certaine perte de précision, mais comme nous parlons ici d'une minueterie pour l'étude et le travail, je juge qu'il n'est pas crucial d'avoir une précision absolue.
```
if (timerDuration - elapsedTime > TICK_RATE) {
    elapsedTime = millis() - timerStartTime;
  } else {
    elapsedTime = timerDuration;
    //La logique de fin de segment va ici...
}
```
Le résultat de ce travail peut être vu dans l'image ci-dessous :
<br/>
<div align="center">
  <img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/7118cc0d-da98-4ad4-a9d0-6b2646958485" />
</div>

<a id="créer-une-machine-à-états"></a>
### Créer une machine à états finis (MÉF)

Ensuite, j'ai commencé à implémenter une machine à états finis pour gérer les états possibles du minuteur. La première itération était aussi simple que possible avec 3 états : WORK, S_BREAK et L_BREAK.
L'implémentation était assez facile, surtout après avoir pris le temps de dessiner ma FSM sur un tableau blanc. Il suffit d'utiliser un switch statement.
<br/>
<div align="center">
  <img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/56cd5906-b2a3-4cff-8959-c05edb07cf6d" />
</div>

<a id="implémenter-une-fonction-pause"></a>
### Implémenter une fonction pause

Le mode pause a été l'une des parties les plus difficiles de ce projet. Il m'a fallu quelques heures pour le résoudre, et j'ai même eu besoin d'un coup de pouce d'une IA. Par contre, je me suis assuré de ne pas le laisser me donner une solution. Normalement, j'utilise énormément l'IA et des exemples sur internet, mais le but ici est d'apprendre et d'améliorer mes compétences pour vraiment comprendre ce que je fais.
La solution pour la pause s'est avérée être en fait assez simple.

Le temps écoulé est habituellement calculé en utilisant la différence entre le temps d'exécution actuel et le temps d'exécution quand la minuterie a été démarré, mais même quand le mode pause est activé, millis() ne s'arrête pas de compter.
En programmation bas niveau, la lecture est faite à partir de l'oscillateur interne (probablement avec un tas de choses simplifiées par la plateforme Arduino), qui ne peut pas être arrêté.
Si le mode pause est activé pendant 30 secondes, millis() a maintenant 30 secondes de trop. Il faut donc retirer ces 30 secondes de millis() pour revenir à l'état de la minuterie avant de la mettre sur pause.

Même en implémentant ceci, j'ai rencontré quelques problèmes. À la sortie du mode pause, la minuterie ne retournait quand-même pas à l'état attendu. Après un peu de débogage, j'ai rapidement réalisé que j'ai besoin de non seulement garder un décompte d'une pause, mais de <em>toutes les pauses</em> jusqu'à ce qu'un nouveau segment commence et que les variables soient remise à 0. Le temps de pause total doit être remis à 0 à ce moment-là aussi. Et maintenant, le mode pause fonctionne correctement. Voici le diagramme FSM mis à jour :

<div align="center">
  <img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/ad76c537-368e-4018-bc0d-352e7a130adc" />
</div>

<a id="créer-un-menu-principal"></a>
### Créer un menu principal

Maintenant que le project commence à prendre forme, j'ai ajouté le menu principal qui permet à l'utilisateur de configurer la durée de chaque segment et de démarrer la minuterie. Cela impliquait beaucoup de défis.

D'abord, j'ai dû créer un système pour gérer les états du menu. J'ai pris beaucoup d'inspiration de ce [tutoriel de All About Circuits](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/).
La logique sous-jacente est la même, mais j'ai énormément modifié le code pour l'adapter à mes besoins. Deux variables contrôlent le menu : une pour l'élément sélectionné et une autre pour savoir si on est dans un sous-menu.

Le deuxième défi était d'afficher le menu. J'ai encore une fois utilisé le tutoriel d'AAC comme base. Quelques manipulations mathématiques de base m'ont permis de centrer dynamiquement les éléments sur l'écran. 
Afficher l'heure était un peu plus délicat. Ma fonction displayTime(), que j'utilisais depuis le début du développement de ce prototype, était mal adaptée pour ceci,
puisqu'elle formatait les millisecondes en format MM:SS ET affichait l'heure sur l'écran. C'est là que j'ai compris que la fonction avait deux rôles, ce qui n'est pas une bonne pratique de programmation,
alors je l'ai divisée en 2 fonctions séparées. displayTime() affiche simplement ce qui est dans mon buffer de temps avec la bonne taille et couleur,
tandis que formatTime() convertit un unsigned long en string de format MM:SS, puis le place dans un tampon juste assez grand pour le contenir.

Le troisième défi était de corriger mes entrées d'encodeur rotatif, qui fonctionnaient bien par elles-mêmes, mais pas lorsqu'un écran est connecté. C'est parce que jusqu'à maintenant, tout mon code était 100% séquentiel.
Cela introduisait beaucoup de délai. J'ai donc dû apprendre à utiliser des interrupts, mais ce n'était honnêtement pas trop difficile. Il faut simplement mettre la valeur qu'on veut lire dans l'une des broches interrupt 
de l'Arduino et de spécifier quelle fonction exécuter quand un changement est détecté.
Et voilà, les contrôles fonctionnent bien mieux maintenant, quoiqu'il y a encore quelques problèmes d'hypersensibilité qui devront être corrigés plus tard.

<div align="center">
  <img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/5b1f8f1c-4e12-4e51-996d-64a9ba550ef2" />
</div>

<a id="implémenter-un-buzzer"></a>
### Implémenter un buzzer

La dernière fonctionnalité majeure à implémenter était un buzzer passif. Le faire fonctionner a été étonnamment difficile. L'option évidente aurait été d'utiliser la fonction delay() d'Arduino, mais cela gèle complètement l'exécution du programme, ce qui ne fonctionne pas
parce que l'affichage doit continuer à se rafraîchir en arrière-plan. L'approche classique millis() ne fonctionne pas non plus, parce que jouer une mélodie composée de notes et de pauses serait impossible. Chaque nouvelle boucle oublierait la dernière note jouée
et ne saurait pas la prochaine note jouer. La seule façon d'empêcher cela est de créer un séquenceur, ce que j'ai fait. À cette fin, j'ai créé un struct appelé "Note", qui contient la fréquence, la durée et le délai d'attente avant la prochaine note. Mettre les Notes dans un tableau permet de construire n'importe quelle mélodie en spécifiant simplement quelles notes sont à jouer. Une variable globale nommée "currentNote" décide où nous en sommes dans la séquence
et est incrémentée par un chaque fois qu'une note est jouée. Sa valeur est -1 si rien ne joue en ce moment.

La deuxième partie du défi avec ce séquenceur était de comprendre comment commencer et terminer une séquence. J'ai décidé d'utiliser une logique simple. Si le délai d'attente jusqu'à la prochaine note est 0, on suppose qu'il n'y a pas de prochaine note. Un peu comme le null terminator pour les chaînes en C. Enfin, j'ai dû élaborer un système pour décider si je voulais démarrer une séquence ou ne rien faire. Ma première idée était d'assumer qu'on voulait démarrer une séquence si la fonction était appelée pendant que currentNote était -1. Mais selon cette logique, si on appelle la fonction à chaque boucle pour vérifier si une mélodie est en cours de lecture, on jouerait tout le temps une mélodie. Je sentait confus et honnêtement plutôt frustré, alors j'ai pris une douche, je me suis fait un café, et j'ai laissé ce problème mariner en arrière-plan.

À mon retour, j'ai eu une nouvelle idée : séparer la fonction en deux. En effet, j'ai décidé de créer deux fonctions nommées playBeepSequence() et updateBeepSequence(). La première démarre une séquence et n'est appelée qu'une seule fois lorsqu'on veut jouer une séquence, tandis que la deuxième est appelée automatiquement à chaque boucle et vérifie si une séquence est en cours de lecture. Si c'est le cas, elle incrémente la note courante de 1 et la joue, mais seulement si le temps d'attente de la note précédente s'est écoulé. Quand la dernière note est atteinte, currentNote est remis à -1, et updateBeepSequence() ne joue plus rien. Pour l'instant, j'ai composé 2 séquences très basiques qu'on pourrait retrouver sur une petite montre achetée au Dollarama, mais j'aimerais inclure des mélodie plus expressives plus tard.

<a id="assembler-le-tout"></a>
### Assemblage final

L'implémentation des fonctionnalités principales de ce prototype est presque terminée... Mais il y a encore quelques ajustements à faire. J'avais gardé le design UI et UX pour la fin, et il est maintenant grand-temps de donner un coup de joli à l'interface. La première chose qui devait disparaître était la police par défaut pour l'affichage du temps, que je trouvais absolument hideuse. Je l'ai remplacée par Sans, l'une des polices offertes par la librairie Adafruit GFX. Elle est inspirée par l'intemporel Helvetica.
Elle a instantanément transformé le look du produit de «gadget de hacker» à «produit sérieux». Constatez vous-même la différence!

<div align="center">
  <img width="30%" height="30%" alt="image" src="https://github.com/user-attachments/assets/0061f9a2-940f-4262-81c7-f1ffc63ab661" />
  <img width="31%" height="31%" alt="image" src="https://github.com/user-attachments/assets/bf916b53-88bc-4455-bb2b-b92bdbedf712" />
</div>
<br/>

Après cette refonte, il me restait quelques petits soucis à régler :

* Il n'y avait pas de rétroaction visible pour faire savoir à l'utilisateur que la minuterie était en mode pause. Oui, le texte en haut dit "Pause", mais il est trop petit ! J'ai fait clignoter l'affichage quand la minuterie est en pause. Il est maintenant bien plus facile de constater que la minuerie est suspendue.
* Quand on démarrait un minuteur, par exemple, 5 minutes, on voyait «05:00» pendant une fraction de seconde, avant de voir «04:59» presque immédiatement. Cela fait un peu bizarre. J'ai ajouté exactement 999 ms à chaque durée du programme.
  De cette façon, il y a une "période de grâce" intégrée où on peut réellement la minuterie démarrer avec sa durée totale.
* Il y avait un léger problème de debounce avec l'encodeur rotatif, spécifiquement lors de la rotation en sens horaire. J'ai corrigé cela en exigeant au moins 2 ms de délai entre les entrées.

<a id="résultat-final"></a>
## Résultat final

Voici le résultat final de mon dur labeur :

<div align="center">
  <img width="55%" height="55%" alt="image" src="https://github.com/user-attachments/assets/74e80ea5-289a-4cb4-9774-4bf50e5c639b" />
  <br/>
  Ceci est une version portable faite avec un Nano V3 et une batterie externe.
  <br/>
  <br/>
  <img width="50%" height="50%"  alt="image" src="https://github.com/user-attachments/assets/bc0879d0-332a-4b03-87c8-1ff3039c5d07" />
  <br/>
  Ici, j'ai connecté l'écran OLED à quelques fils Dupont et l'ai mais sur un support de téléphone pour le rendre plus visible.
</div>

<!-- CONCLUSION -->
<a id="conclusion"></a>
## Conclusion

Je suis plutôt fier de ce que j'ai accompli jusqu'à présent et j'en ai beaucoup appris pas mal à travers ce processus. Avec du recul, voici ce que je ferais différemment compte tenu de mes nouvelles connaissances :
<ul>
  <li>Être plus diligent lors de la recherche de pièces. Si j'avais passé plus de temps à réfléchir à ce que je voulais exactement faire avec chaque composant, j'aurais pu économiser de l'argent sur des choses que je n'ai pas utilisé ou que je vais devoir remplacer dans le futur.</li>
  <li>Utiliser Git dès le départ. Vous lisez actuellement cet article sur GitHub, donc j'ai évidemment changé d'avis plus tard, mais je ne l'ai pas fait au début parce que je pensais que ce projet était trop simple pour cela. J'avais tort.</li>
</ul>

Ceci n'est que le début, et je prévois de concevoir un produit de A à Z.
Voici la ligne du temps que j'ai en tête pour y arriver :

- [x] Créer un prototype Arduino
- [ ] Créer un prototype STM32
- [ ] Concevoir et produire un PCB
- [ ] Concevoir et produire un boîtier
- [ ] Faire l'assemblage final

Entre-temps, j'utilise ce prototype pendant mes sessions d'étude et je prends note des fonctionnalités à ajouter et des ajustements à faire pour la prochaine itération.
Je me suis bien amusé pendant la conception de ce prototype, et je me sens incroyablement motivé par ce projet. Si vous vous êtes rendus jusqu'ici dans votre lecture, 
je vous remercie sincèrement de m'avoir lu, et j'espère que vous en avez tiré quelque chose.

<!-- CONTACT -->
<a id="contact"></a>
## Contact

Voulez-vous prendre un café avec moi? Travailler avec moi? Me faire travailler <em>pour</em> vous ? Vous pouvez me trouver ici :

Courriel - salif8514@gmail.com<br/>
LinkedIn - https://www.linkedin.com/in/salif-d-b567011ba/

<!-- ACKNOWLEDGMENTS -->
<a id="remerciements"></a>
## Remerciements

* [L'excellente série de Paul McWorther sur les bases d'Arduino](https://www.youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP)
* [Le tutoriel de All About Circuits](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/)
* [Cette merveilleuse explication des interrupts ainsi que des minuteries Arduino](https://www.circuitbasics.com/how-to-use-hardware-interrupts-and-timer-interrupts-on-the-arduino/)

<p align="right">(<a href="#readme-top">Retour au haut de la page</a>)</p>
