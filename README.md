<br />
<div align="center">
  <a href="https://github.com/Poivre31/Tomographie/">
    <img src="resources/brain.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Méthodes numériques de tomographie</h3>

  <p align="center">
    Un projet numérique sur la reconstruction d'image acquises par tomographie!
    <br />
    <a href="https://example.com/">Voir une démo</a>
    &middot;
    <a href="https://github.com/Poivre31/Tomographie/issues/new?labels=bug&template=bug-report---.md">Déclarer un bug</a>
  </p>
</div>


## A propos de la tomographie


Dans de nombreux domaines (astrophysique, géophysique et tout particulièrement l'imagerie médicale), il est impossible de mesurer de manière directe une grandeur à l'intérieur d'un objet. Soit parce que cet objet est trop loin (astro), qu'on ne peut pas creuser son intérieur (géo) ou qu'on peut le faire... mais qu'on ne préfère pas ! (médical)
Dans ce contexte, la tomographie permet de reconstruire l'intérieur de cet objet à partir de mesures effectuées depuis son extérieur. Par exemple, les géophysiciens ont accès aux données séismologies, influencées directement par la structure de la Terre. Dans le domaine médical, plusieurs méthodes d'imagerie (IRM, les scanner à rayon X) permettent de mesurer des projections à travers l'objet. L'enjeu est alors de reconstruire l'intérieur de l'objet à partir de ces mesures. C'est un problème inverse difficile qui a attiré l'attention de nombreux chercheurs. Un des résultats fondamentaux en tomographie est le Théorème de la tranche centrale de Fourier, qui relie le sinograme (l'ensemble des projections mesurées) à l'objet par la transformation de Fourier.

Le but de ce projet est dans un premier temps de simuler les données obtenues dans un appareil tomographique. Ici, la projection à un couple angle,distance donné, c'est à dire  l'intégrale de la densité de l'objet selon le rayon asssocié, est calculé par la méthode des rectangles à pas variables. Les intersections du rayon avec la grille de pixels permettent de calculer les différents pas. Il est aussi possible d'affiner la simulation des données en ajoutant divers bruits. 

Ensuite, l'image est reconstruite à parir du théorème de la tranche centrale:
- la transformée de fourier de chaque projection (ensemble des intégrales à toutes les distances mesurées pour un angle fixé) est calculée
- ces données polaires sont interpolées sur une grille cartésienne à l'aide d'interpolation bilinéaire, donnant ainsi la transformée de Fourier 2D de l'image
- l'image est reconstruite par transformation de fourier inverse

Cette méthode présente un enjeu d'interpolation intéressant et de meilleures performances que son alternative directe, la rétroprojection filtrée, c'est pour cela qu'elle a été choisie ici. Cependant c'est cette dernière qui est couramment utilisée dans l'industrie, notamment pour éviter ces problématiques d'interpolation.

Pour un nombre de projections insuffisant, ce qui est souvent le cas à cause des contraintes réelles, la reconstruction dans le domaine de fourier est incomplète ce qui mène à la présence d'artefacts de reconstrucction dans le domaine spatial. Plusieurs méthodes permettent d'atténuer ce défaut: le filtrage par une fenetre de Shepp-Logan ou de Hann par exemple et la détection compressée. Cette dernière est au centre des dernières avancées dans le domaine et sera implémentée dans le futur.

## Utiliser le projet

Voici les instructions à suivre pour installer et utiliser le projet.

### Dépendances

* Le projet est construit sous Linux qui est pour le moment nécessaire. Il peut en effet être compilé/linké sous Windows mais les script d'éxecution sont écrits pour un système Linux.
* CMake 3.23 ou plus est requis pour compiler le projet.
* Python 3.xx est nécessaire. Pour l'import et l'affichage des images, il faut de plus que les librairies `matplotlib`,`numpy` et `PIL`soient installées pour cette installation python. Si ce n'est pas le cas:
```sh
    sudo apt install python3-matplotlib
    sudo apt install python3-numpy
    sudo apt install python3-pillow
```

### Installation
Il suffit de cloner le répertoire:
 ```sh
 git clone https://github.com/Poivre31/Tomographie.git
 ```
puis de se réferer à `Utilisation` pour compiler le projet et exécuter le programme.

### Utilisation

Le dossier `run` contient plusieurs scripts pour effectuer divers taches, comme compiler le projet, calculer uniquement le sinograme ou faire la reconstruction d'une traite...

L'image à étudier et les parametres du calcul sont à définir dans le fichier `config.txt` qui peut etre directement edité par le script `configure.sh`. Il est possible d'écrire `shepp-logan`, `rectangle` ou `ellipse` pour utiliser les formes par défaut, ou de donner le nom d'une image png dans le dossier ressources pour l'utiliser comme réference. Il suffira alors d'écrire `brain.png` par exemple.

Les executions du programme suivantes utiliserons alors ces parametres.

Pour executer un des scripts, il faut d'abord donner l'autorisation d'execution. Depuis le dossier principal:
```sh
chmod 755 run -R
```
Puis simplement executer le script depuis le dossier run. Par exemple, pour compiler puis calculer le sinograme et la reconstruction:
```
cd run
./build_and_run.sh
```


## Roadmap

- [x] Améliorer la qualité de l'algorithme de reconstruction
- [ ] Améliorer les performances de l'algorithme de projection
- [ ] Ajouter une interface utilisateur
- [ ] Utiliser l'accéleration GPU
- [ ] Expérimenter avec la détection compressée
    - [ ] Décomposition en ondelettes
    - [ ] Alogithme de Basis Pursuit Denoising
- [ ] Support des systèmes
    - [x] Linux
    - [/] Windows
- [ ] Support des langues
    - [/] English
    - [/] Francais

Les problèmes ouverts sont disponibles ici [open issues](https://github.com/Poivre31/Tomographie/issues).

## License

Distribué selon la GNU General Public License. Voir `LICENSE.txt` pour plus de détails.

## Contact

Raphaël Boisard - raphael.boisard@utoulouse.fr

<p align="right">(<a href="#readme-top">back to top</a>)</p>
