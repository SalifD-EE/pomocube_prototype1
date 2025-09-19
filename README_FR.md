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

En tant qu'étudiant en génie électrique, je suis bien conscient qu'obtenir simplement le diplôme ne suffit pas pour se démarquer lors de la recherche d'emploi ou de stage, surtout dans le marché du travail actuel.
Une stratégie courante pour contrer cela consiste à travailler sur des projets personnels pendant son temps libre, mais étant aussi ingénieur, autant en profiter pour résoudre un problème dans ma vie. Voici le Pomocube.

<a id="quest-ce-quun-pomodoro"></a>
### Qu'est-ce qu'un pomodoro ?

Nommée d'après le minuteur de cuisine en forme de tomate, la technique pomodoro est une façon de rester concentré pendant de longues périodes. Vous travaillez pendant 25 minutes, puis prenez une pause de 5 minutes, et répétez ce processus 3 fois de plus, avec une pause plus longue à la fin.
En prenant de petites pauses régulières, vous permettez à votre attention de se recharger, vous gardant plus productif dans l'ensemble. De plus, vous avez toujours une petite récompense à anticiper. Chacun est différent, mais j'ai personnellement eu beaucoup de succès avec cette technique pour étudier et travailler.

Bien sûr, il existe déjà beaucoup d'applications pomodoro, et j'en ai utilisé ma part au fil des années (ma préférée est [Flow](https://www.flow.app/)).
Ceci dit, vous vous demandez peut-être pourquoi j'entreprends ce projet. Voici quelques raisons :

* J'ai besoin d'un projet personnel, et celui-ci offre un équilibre parfait entre simplicité, pertinence et utilité.
* Les applications pomodoro de bureau prennent souvent un espace écran précieux et ne se synchronisent parfois pas entre les plateformes.
* Les applications mobiles consomment une batterie précieuse, nécessitent un support et vous forcent à garder votre téléphone près de vous.
* Peu importe l'appareil utilisé, vous téléchargez <em>encore une autre application</em>, et j'en ai ASSEZ des applications.

C'est alors que j'ai commencé à penser à créer un petit minuteur physique mignon qui soit élégant, agréable à utiliser et transportable partout.
Je veux que l'appareil soit simple et à usage unique, une courte pause par rapport aux tablettes de verre et de métal hyper-connectées d'aujourd'hui.
Voici un petit rendu de ce à quoi j'imagine que la version finale ressemblera :
<br/>
<div align="center">
  <img width="40%" height="40%" alt="rendu pomocube" src="https://github.com/user-attachments/assets/b528b48f-cb07-4bba-9183-2ecd1d8c3783" />
</div>
<br/>

L'ingénierie et l'apprentissage prennent tous deux du temps, alors j'ai choisi de travailler par itérations plutôt que d'essayer d'atteindre ce résultat final immédiatement. Ce premier prototype vise à
implémenter quelques fonctionnalités de base. Les révisions ultérieures utiliseront différents composants et comporteront des fonctionnalités étendues.


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

Oui, j'utilise un Arduino, mais laissez-moi m'expliquer. La vérité est que je ne savais pas mieux quand j'ai commencé à bricoler avec le développement embarqué.
Au moment où j'ai appris que ce MCU est très vieux et que la plateforme Arduino simplifie beaucoup de choses, j'avais déjà acheté de l'équipement,
alors j'ai décidé de faire un prototype rapide avec ce que j'avais pour me mouiller les pieds et avoir quelque chose à montrer au salon de l'emploi de mon école,
qui a lieu dans 2 semaines au moment où j'écris ces lignes. L'intention n'a jamais été de faire la version finale avec ce MCU ou avec l'IDE Arduino.
Je prévois utiliser le STM32-F446RE beaucoup plus puissant à la place. Pour cette première itération cependant, cela fera l'affaire.

<a id="écran"></a>
### Écran - 0.96" SSD1306 OLED Monochrome

Cet écran est bon marché, a beaucoup de support et de documentation, et semble très net. Mon interface utilisateur contient beaucoup d'espace vide, ce qui se marie bien
avec les noirs profonds pour lesquels les OLED sont connus. Ce projet est assez simple pour ne pas nécessiter de communication haute vitesse, donc la configuration à 2 câbles de l'I²C
aide également à réduire l'encombrement des câbles.

<a id="encodeur-rotatif"></a>
### Encodeur rotatif - KY-40

Cet encodeur rotatif est la seule forme d'entrée pour cet appareil. Il est satisfaisant à faire tourner et assez intuitif.
Le bonus supplémentaire du KY-40 est qu'il est soudé à un PCB qui inclut déjà les résistances dont vous avez besoin pour filtrer
le bruit des signaux SW, CLK et DT. Cela le rend un peu plus difficile à sécuriser sur une planche à pain, mais je peux m'en accommoder.

<a id="buzzer-passif"></a>
### Buzzer passif

C'est celui qui est venu avec mon kit de démarrage Arduino. Il fait le travail.

<a id="schéma-de-câblage"></a>
### Schéma de câblage

<div align="center">
  <img width="40%" height="40%" alt="{C89FDA2B-B4BD-4FD9-9956-544990561FB0}" src="https://github.com/user-attachments/assets/bffef6d4-cfb3-4b5c-992a-340779c5e63c" />
</div>

<!-- THE PROCESS -->
<a id="le-processus"></a>
## Le processus

### Faire fonctionner l'encodeur
<a id="faire-fonctionner-lencodeur"></a>
J'ai commencé par tester l'encodeur rotatif. C'est assez simple de le faire
fonctionner avec l'Uno R3. Le seul petit problème que j'ai rencontré est que mon encodeur avait ses capteurs DT et CLK inversés par rapport au tutoriel que je suivais,
ce qui l'amenait à lire les directions de manière inversée (CW était détecté comme CCW et vice versa). C'est une bonne chose parce que cela m'a forcé à comprendre
comment l'appareil fonctionne réellement. La solution était simplement d'inverser la logique dans le code de DT != CLK à DT == CLK.

<div align="center">
  <img width="371" height="441" alt="image" src="https://github.com/user-attachments/assets/f5e2d0a1-2fed-4f4c-a66a-c00109776211" />
</div>

<a id="afficher-un-minuteur"></a>
### Afficher un minuteur
Avec l'encodeur fonctionnel, ma tâche suivante était de faire fonctionner cet OLED. D'abord, j'ai dû choisir entre utiliser une bibliothèque, suivre un tutoriel, ou écrire la logique moi-même.
J'ai opté pour utiliser la bibliothèque Adafruit GFX pour gérer le dessin des pixels réels, avec la logique du minuteur réelle faite par votre serviteur.

J'ai utilisé la fonction millis() d'Arduino comme base, qui compte combien de temps en millisecondes s'est écoulé depuis le démarrage. Ma logique est principalement centrée autour de
l'enregistrement de la valeur de millis() quand le minuteur démarre, la définition de combien de temps je veux que le minuteur fonctionne, et faire diverses conversions et mathématiques simples pour déterminer quoi afficher.

```
elapsedTime = millis() - timerStartTime;
```

Un petit défi était d'afficher des zéros en tête quand il y a moins de 10 secondes dans un segment donné. J'ai fini par décider d'une logique simple.
Ajoutez simplement un zéro d'abord si le nombre de secondes ou minutes à afficher est inférieur à 10. Facile.

```
if (minDisplay < 10) display.print("0"); //Zéro en tête
display.print(minDisplay);
```

Le prochain défi était de gérer la fin d'un segment. Au début, je pensais que j'avais juste besoin de vérifier si le temps restant était supérieur à zéro.
Mais faire cela a résulté en un minuteur sautant d'une manière ou d'une autre à un temps complètement aléatoire. Pourquoi ? J'ai imprimé le temps restant sur le moniteur série pour comprendre ce qui se passait (l'Uno ne supporte pas le débogage, hélas).

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

Puis j'ai compris. Un regard plus attentif révèle que le minuteur interne de l'ATmega 328P a un taux de tick d'environ 45 ms à 16 MHz, donc si le temps restant était plus petit que ce tick, nous irions dans les négatifs, sauf qu'il n'y <em>a</em> pas de négatifs,
parce que le temps est géré avec des unsigned longs, alors au lieu nous débordon à la valeur la plus élevée possible pour ce type de variable, qui est environ 4,29 milliards. C'est pourquoi nous passons de 16 à ces nombres ridiculement énormes.
La solution était de mettre à jour le minuteur seulement si le temps restant était à plus d'un tick de zéro, sinon, le segment est terminé, et le minuteur s'arrête. Vous perdez un peu de précision à cause de cette limitation, mais 50-60 millisecondes ne sont pas cruciales pour ce qui n'est rien de plus qu'un petit minuteur d'étude.

```
if (timerDuration - elapsedTime > TICK_RATE) {
    elapsedTime = millis() - timerStartTime;
  } else {
    elapsedTime = timerDuration;
    //La logique de fin de segment va ici...
}
```
Cela a résulté en un minuteur fonctionnel, bien que rudimentaire, que vous pouvez voir ici :
<br/>
<div align="center">
  <img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/7118cc0d-da98-4ad4-a9d0-6b2646958485" />
</div>

<a id="créer-une-machine-à-états"></a>
### Créer une machine à états finis (FSM)

Ensuite, j'ai commencé à implémenter une machine à états finis pour gérer les états possibles du minuteur. La première itération était aussi simple que possible avec 3 états : WORK, S_BREAK et L_BREAK.
Les implémenter avec une déclaration switch était assez facile, surtout après avoir pris le temps de dessiner ma FSM sur un tableau blanc.
<br/>
<div align="center">
  <img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/56cd5906-b2a3-4cff-8959-c05edb07cf6d" />
</div>

<a id="implémenter-une-fonction-pause"></a>
### Implémenter une fonction pause

C'était l'une des parties les plus difficiles de ce projet. Il m'a fallu quelques heures pour le résoudre, et j'ai même eu besoin d'un coup de pouce d'un LLM. J'ai fait attention à ne pas le laisser me donner une solution cependant. Normalement, j'utilise les LLMs et les exemples extensivement, mais le but ici est d'apprendre et d'aiguiser mes compétences pour vraiment comprendre ce que je fais.
La solution pour la pause s'est avérée être en fait assez simple.

Le temps écoulé est habituellement calculé en utilisant la différence entre le temps d'exécution actuel et le temps d'exécution quand le minuteur a été démarré, mais quand vous mettez en pause, millis() ne s'arrête pas de compter.
À un niveau bas comme celui-ci, nous lisons plus ou moins de l'oscillateur (probablement avec un tas de choses simplifiées par la plateforme Arduino), qui ne peut pas être arrêté.
Si vous mettez en pause pendant 30 secondes, millis() a maintenant 30 secondes de plus que ce que vous attendez. Donc tout ce que vous devez faire est de retirer ces 30 secondes de millis(), et vous êtes de retour à l'état exact où vous étiez avant de mettre en pause.

Même en implémentant ceci, j'ai rencontré quelques problèmes. Le temps ajouté en arrière n'avait aucun sens. Après un débogage rudimentaire, j'ai rapidement réalisé que j'ai besoin de garder un décompte non seulement d'une pause, mais de <em>toutes les pauses</em> jusqu'à
ce qu'un nouveau segment commence et que l'heure de début soit remise à 0. Le temps de pause total doit être remis à 0 à ce moment-là aussi. Et maintenant, la pause fonctionne comme elle le devrait. Quand elle l'a fait, une poussée d'excitation et de satisfaction a couru à travers mon corps
et j'ai chuchoté "fils de p***" à moi-même. Voici le diagramme FSM mis à jour :

<div align="center">
  <img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/ad76c537-368e-4018-bc0d-352e7a130adc" />
</div>

<a id="créer-un-menu-principal"></a>
### Créer un menu principal

Avec le projet qui commençait vraiment à prendre forme, j'ai ajouté le menu principal qui vous permet de configurer vos durées et de démarrer le minuteur. Cela impliquait beaucoup de défis.

D'abord, j'ai dû inventer un système pour gérer les états du menu. J'ai pris une inspiration libérale de ce [tutoriel All About Circuits](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/).
Ce n'était pas un simple copier-coller cependant. La logique sous-jacente est la même, mais j'ai lourdement modifié le code pour l'adapter à mes besoins. Deux variables pilotent le menu : une pour quel élément est sélectionné et une autre pour savoir si vous l'ajustez ou non.

Le deuxième défi était de dessiner le menu. J'ai encore une fois utilisé le tutoriel d'AAC comme base. Il ne m'a fallu que de simples déclarations if-else pour déterminer si chaque élément était mis en évidence ou non.
Quelques mathématiques de base impliquant les limites de texte m'ont également permis de centrer dynamiquement les éléments sur l'écran. Afficher l'heure était un peu plus délicat. Ma fonction displayTime() précédente était mal adaptée pour ceci,
puisqu'elle formatait les millisecondes en format MM:SS et affichait l'heure sur l'écran. C'est quand j'ai compris que la fonction avait deux rôles, ce qui n'est généralement pas une bonne pratique,
alors je l'ai divisée en 2 fonctions séparées. displayTime() fait ce qu'elle dit et affiche simplement ce qui est dans mon tampon de temps avec la bonne taille et couleur,
tandis que formatTime() convertit un unsigned long en format MM:SS réel, puis le place dans un tampon juste assez grand pour le contenir.

Le troisième défi était de corriger mes entrées d'encodeur rotatif, qui fonctionnaient bien seules, mais étaient soit mal lues soit pas lues du tout quand jumelées avec un affichage. C'est parce que jusqu'à maintenant, tout mon code était 100% séquentiel dans la boucle.
Cela introduisait beaucoup de retards. Donc j'ai dû apprendre les interruptions, mais ce n'était honnêtement pas trop difficile. Tout ce que vous avez à faire est de brancher la valeur que vous voulez lire dans l'une des broches d'interruption de l'Arduino et lui dire quelle fonction exécuter quand un changement est détecté.
Et voilà, c'est beaucoup plus réactif maintenant, bien qu'avec quelques problèmes de hypersensibilité avec les rotations dans le sens horaire qui devront être corrigés plus tard.

<div align="center">
  <img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/5b1f8f1c-4e12-4e51-996d-64a9ba550ef2" />
</div>

<a id="implémenter-un-buzzer"></a>
### Implémenter un buzzer

La dernière fonctionnalité majeure à implémenter était un buzzer passif. Le faire fonctionner était étonnamment difficile. L'option évidente aurait été d'utiliser simplement la fonction delay() d'Arduino, mais cela arrête complètement tout le programme, ce qui ne fonctionne pas
parce que l'affichage doit continuer à se rafraîchir en arrière-plan. L'approche classique millis() ne fonctionne pas non plus, parce que jouer une mélodie composée de différentes notes et pauses serait impossible. Chaque nouvelle boucle oublierait la dernière note jouée
et ne saurait pas laquelle jouer ensuite. La seule façon d'empêcher cela est de créer un séquenceur, ce que j'ai fait. À cette fin, j'ai créé une structure appelée "Note", qui contient la fréquence, la durée et plus important encore,
combien de temps attendre jusqu'à la prochaine note. Mettre les Notes dans un tableau permet de construire n'importe quelle mélodie en spécifiant simplement quelles notes jouer manuellement. Une variable globale nommée "currentNote" décide où nous en sommes dans la séquence
et est incrémentée de un chaque fois qu'une note est jouée. Sa valeur est -1 si rien ne joue en ce moment.

La deuxième partie du défi avec ce séquenceur était de comprendre comment commencer et terminer une séquence. J'ai décidé d'utiliser une logique simple pour ce dernier. Si vous attendez 0 ms jusqu'à la prochaine note, on suppose que c'est parce qu'il n'y a pas de prochaine note. Cela fonctionne un peu comme le terminateur nul pour les chaînes en C. Finalement, j'ai dû comprendre comment décider si je voulais ou non démarrer une séquence ou ne rien faire. Ma première idée était d'assumer que vous vouliez démarrer une séquence si vous appeliez la fonction pendant que currentNote était -1. Mais avec cette logique, si vous appelez la fonction à chaque boucle pour vérifier si vous jouez quelque chose, alors vous joueriez quelque chose en répétition. Je me suis senti vraiment confus pendant un moment, alors j'ai pris une douche, fait du café, et j'ai laissé ce problème tranquille.

En revenant à mon bureau, j'ai eu une nouvelle idée : diviser le tout premier ton et tous les autres en 2 fonctions appelées playBeepSequence() et updateBeepSequence() respectivement. La première lance une séquence et n'est appelée qu'une seule fois quand vous voulez jouer une séquence, tandis que la dernière est appelée à chaque boucle et vérifie si une séquence est en cours de lecture. Si c'est le cas, alors elle incrémente currentNote de 1 et le joue, mais seulement si le temps d'attente de la note précédente s'est écoulé. Quand la dernière note est atteinte, currentNote est remis à -1, attendant le prochain appel de playBeepSequence(). Pour l'instant, je n'ai que 2 séquences très basiques qui sonnent comme un minuteur de magasin à un dollar, mais plus tard, faire des mélodies plus expressives est définitivement dans les cartes.

<a id="assembler-le-tout"></a>
### Assembler le tout

Avec ceci, toute la fonctionnalité principale pour ce minuteur était complète... Mais il y avait encore quelques ajustements de qualité de vie à faire. J'avais reporté presque chaque fonctionnalité d'interface utilisateur et d'expérience utilisateur jusqu'à la fin, alors maintenant c'est le temps de s'attaquer à cela. La première chose qui devait disparaître était cette police par défaut épouvantable pour l'affichage du temps. Je l'ai remplacée par Sans, l'une des polices offertes par la bibliothèque Adafruit GFX. Elle est inspirée par la pérenne Helvetica et elle semble géniale.
Elle a instantanément transformé le sentiment du produit d'un gadget de hacker à un vrai produit utilisé par de vraies personnes. Je veux dire, voyez la différence par vous-même.

<div align="center">
  <img width="30%" height="30%" alt="image" src="https://github.com/user-attachments/assets/0061f9a2-940f-4262-81c7-f1ffc63ab661" />
  <img width="31%" height="31%" alt="image" src="https://github.com/user-attachments/assets/bf916b53-88bc-4455-bb2b-b92bdbedf712" />
</div>
<br/>

Après ceci, j'avais quelques mouches plus ennuyeuses à écraser pour le polissage supplémentaire :

* Il n'y avait pas de rétroaction visible et évidente pour faire savoir à l'utilisateur que le minuteur était en pause. Oui, le texte en haut dit "Pause", mais c'est trop petit ! J'ai fait clignoter l'affichage quand le minuteur est en pause, ce qui le rend significativement plus facile à dire d'un coup d'œil que le minuteur est suspendu.
* Quand vous démarriez un minuteur à, disons, 5 minutes, vous verriez "05:00" pour une fraction de seconde, puis il diminuerait immédiatement à "04:59". Je sais pourquoi cela arrive et cela fait sens, mais c'est choquant. Ceci a été résolu en ajoutant sournoisement exactement 999 ms à chaque durée unique.
  De cette façon, il y a une "période de grâce" intégrée où vous pouvez réellement voir combien de temps vous avez mis.
* Il y avait un léger problème de débondissement avec l'encodeur rotatif, spécifiquement lors de la rotation dans le sens horaire. J'ai corrigé cela en exigeant au moins 2 ms de délai entre les entrées. Plus et trop d'entrées étaient sautées. Moins et le problème n'était simplement pas corrigé.
  Cela ne se sent toujours pas aussi bien que je le voudrais, mais ça devra faire pour cette itération.

<a id="résultat-final"></a>
## Résultat final

Après avoir commandé un Nano V3, ~~volé~~ emprunté la batterie externe de ma sœur et fait une gestion rapide des câbles pour rendre le tout portable, voici le résultat final :

<div align="center">
  <img width="55%" height="55%" alt="image" src="https://github.com/user-attachments/assets/74e80ea5-289a-4cb4-9774-4bf50e5c639b" />
  <br/>
  Ceci est une version portable faite avec un Nano V3 et une batterie externe.
  <br/>
  <br/>
  <img width="50%" height="50%"  alt="image" src="https://github.com/user-attachments/assets/bc0879d0-332a-4b03-87c8-1ff3039c5d07" />
  <br/>
  Ici, j'ai connecté l'écran OLED à quelques fils Dupont et l'ai appuyé sur un support de téléphone pour une visualisation plus facile.
</div>

<!-- CONCLUSION -->
<a id="conclusion"></a>
## Conclusion

Je suis fier de ce que j'ai accompli jusqu'à présent et j'ai beaucoup appris du processus. En regardant en arrière, voici ce que je ferais différemment avec ce que je sais maintenant :
<ul>
  <li>Être plus diligent lors de la recherche de pièces. Si j'avais passé plus de temps à réfléchir à ce que je voulais exactement faire avec chaque composant, j'aurais pu économiser de l'argent sur des choses que je n'ai pas fini par utiliser ou devrai remplacer plus tard, surtout pour l'affichage.</li>
  <li>Utiliser le contrôle de version dès le début. Vous lisez actuellement ceci sur GitHub, donc j'ai évidemment changé d'avis plus tard, mais je ne l'ai pas fait au début parce que je pensais que ce projet était trop petit pour le nécessiter. J'avais tort.</li>
</ul>

Et pourtant, comme vous prenez des leçons du passé, vous devez aussi regarder vers l'avenir. Ce n'est que le commencement, et je prévois vraiment concevoir un vrai produit de A à Z.
Voici la feuille de route que j'ai en tête pour y arriver :

- [x] Créer un prototype basé sur Arduino
- [ ] Créer un prototype STM32
- [ ] Concevoir et produire un PCB
- [ ] Concevoir et imprimer en 3D un boîtier
- [ ] Faire la construction finale

Entre-temps, j'utilise ce prototype pendant mes études et je prends des notes sur les fonctionnalités à ajouter et les ajustements à faire dans la prochaine itération.
C'était sérieusement vraiment amusant à faire, et je ne me suis pas senti aussi motivé par un projet personnel depuis des années. Si vous avez lu jusqu'ici dans mon
compte-rendu, vous avez la patience d'un saint, parce que bon sang c'était long. Merci d'avoir lu, et j'espère que vous en avez tiré quelque chose.

<!-- CONTACT -->
<a id="contact"></a>
## Contact

Voulez-vous prendre contact ? Travailler avec moi ? Me faire travailler <em>pour</em> vous ? Vous pouvez me trouver ici :

Courriel - salif8514@gmail.com<br/>
LinkedIn - https://www.linkedin.com/in/salif-d-b567011ba/

<!-- ACKNOWLEDGMENTS -->
<a id="remerciements"></a>
## Remerciements

* [L'excellente série de Paul McWorther sur Arduino](https://www.youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP)
* [Ce tutoriel All About Circuits](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/)
* [Ce gars expliquant les interruptions d'une façon qui fait sens](https://www.circuitbasics.com/how-to-use-hardware-interrupts-and-timer-interrupts-on-the-arduino/)

<p align="right">(<a href="#readme-top">retour au sommet</a>)</p>