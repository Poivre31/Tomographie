<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Poivre31/Tomographie/">
    <img src="resources/brain.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Tomographie</h3>

  <p align="center">
    Un projet numérique sur la reconstruction d'image acquises par tomographie!
    <br />
    <a href="https://example.com/">Voir une démo</a>
    &middot;
    <a href="https://github.com/Poivre31/Tomographie/issues/new?labels=bug&template=bug-report---.md">Déclarer un bug</a>
  </p>
</div>


<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

Dans de nombreux domaines (astrophysique, géophysique et tout particulièrement l'imagerie médicale), il est impossible de mesurer de manière directe une grandeur à l'intérieur d'un objet. Soit parce que cet objet est trop loin (astro), qu'on ne peut pas creuser son intérieur (géo) ou qu'on peut le faire... mais qu'on ne préfère pas ! (médical)
Dans ce contexte, la tomographie permet de reconstruire l'intérieur de cet objet à partir de mesures effectuées depuis son extérieur. Par exemple, les géophysiciens ont accès aux données séismologies, influencées directement par la structure de la Terre. Dans le domaine médical, plusieurs méthodes d'imagerie (IRM, les scanner à rayon X) permettent de mesurer des projections à travers l'objet. L'enjeu est alors de reconstruire l'intérieur de l'objet à partir de ces mesures. C'est un problème inverse difficile qui a attiré l'attention de beaucoup de chercheurs. 

## Getting Started

Voici les instructions à suivre pour installer et utilsier le projet.

### Dépendances

* Le projet est construit sous Linux qui est pour le moment nécessaire. Il peut en effet être compilé/linké sous Windows mais les script d'éxecution sont écrits pour un système Linux.
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
puis de se réferer à `Utilisation`

<!-- USAGE EXAMPLES -->
### Utilisation

Le dossier `run` contient plusieurs scripts pour effectuer divers taches, comme `build` le projet, calculer uniquement le sinograme ou faire la reconstruction d'une traite... L'image à étudier et les parametres du calcul sont à définir dans le fichier `config.txt` qui peut etre directement edité par le script `configure.sh`. Les executions du programme suivantes utiliserons alors ces parametres.

Pour executer un des scripts, il faut d'abord donner l'autorisation d'execution. Depuis le dossier principal:
```sh
sudo chmod run 755 -R
```
Puis simplement executer le script depuis le dossier run. Par exemple, pour build puis calculer le sinograme et la reconstruction:
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
