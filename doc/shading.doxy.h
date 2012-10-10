/**
 * @~english
 * @taomoduledescription{Shading, Shading}
 * Apply some shading effects which allow to create non-photorealistic rendering (cartoon-style). @n
 * Following images show the difference between a classic rendering and an other one obtained with shading effects.
 *
 * <em>Classic rendering</em> :
 * @include shading.ddd
 * @image html shading.png "Classic rendering"
 *
 * @~french
 * @taomoduledescription{Shading, Effets Shading}
 * Applique des effets de type <em>shading</em> (ombrage) qui permettent de réaliser des rendus graphiques non-photoréalistes (style cartoon).
 * Les images suivantes présentent la différence entre le rendu classique et le rendu obtenu avec ces effets de shading. @n
 *
 * <em>Rendu classique</em> :
 * @include shading.ddd
 * @image html shading.png "Rendu classique"
 *
 * @~
 *
 * <em>Cel shading</em> :
 * @include cel.ddd
 * @image html cel.png "Cel shading"
 *
 * <em>Gooch shading</em> :
 * @include gooch.ddd
 * @image html gooch.png "Gooch shading"
 *
 * @endtaomoduledescription{Shading}
 * @{
 */

/**
 * @~english
 * Defines color for <em>cel shading</em> with its r, g, b values.
 * @~french
 * Définit la couleur pour l'effet <em>cel shading</em> à partir de ses valeurs r, g, b.
 * @~
 * @see cel_shading
 */
cel_color(r:real, b:real, g:real);

/**
 * @~english
 *  Apply <em>cel shading</em> on current scene.
 *  Add a <em>cel shading</em> effect to make the current scene appear to be hand-drawn.
 *
 *  It can be used to mimic the style of a comic book or cartoon in
 *  changing current color (or texture) in a toon one define by @ref cel_color.
 *
 *  @note This effect can support a maximum of 8 differents lights.
 *  @see For further informations, see <a href="http://en.wikipedia.org/wiki/Cel-shaded_animation">Wikipedia</a>
 *
 * @~french
 * Active l'effet <em>cel shading</em>.
 * Ajoute un effet de <em>cel shading</em> (Ombrage de celluloïd) afin de rendre la scène courante comme si elle était dessiné à la main.
 *
 * Il peut ainsi être utiliser pour imiter le style d'une bande dessiné ou d'un cartoon en changeant la couleur courante
 * (ou la texture) par une autre plus \e cartoon définit par @ref cel_color.
 *
 * @note Cet effet peut supporter jusqu'à 8 sources de lumières différentes.
 * @see Pour plus d'informations, voir <a href="http://fr.wikipedia.org/wiki/Ombrage_de_celluloïd">Wikipedia</a>
 */
cel_shading();


/**
 * @~english
 * Define warm diffuse coefficient for the <em>Gooch shading</em> effect.
 * This coefficient is used to mix the warm color define by @ref warm_color with others.
 *
 * Its default value is 0.45.
 *
 * @~french
 * Définit le coefficient de couleur chaude pour l'effet
 * <em>Gooch shading</em>.
 * Ce coefficient agit sur la façon dont la couleur chaude (@ref warm_color)
 * est mélangée aux autres couleurs.
 *
 * La valeur par défaut est 0.45.
 *
 * @~
 * @see warm_color, gooch_shading
 */
warm_diffuse(w:real);

/**
 * @~english
 * Define cool diffuse coefficient for the <em>Gooch shading</em> effect.
 * This coefficient is used to mix the cool color define by @ref cool_color with others.
 *
 * Its default value is 0.045.
 *
 * @~french
 * Définit le coefficient de couleur froide pour l'effet
 * <em>Gooch shading</em>.
 * Ce coefficient agit sur la façon dont la couleur froide (@ref cool_color)
 * est mélangée aux autres couleurs.
 *
 * La valeur par défaut est 0.045.
 *
 * @~
 * @see cool_color, gooch_shading
 */
cool_diffuse(c:real);

/**
 * @~english
 * Define warm color by its r, g, b values.
 * This color is used for <em>Gooch shading</em> effect.
 * Warm color indicates surfaces facing toward the light source.
 *
 * @~french
 * Définit la couleur chaude pour l'effet <em>Gooch shading</em>.
 * La couleur chaude met en évidence les surfaces qui font face à la source
 * lumineuse.
 *
 * @~
 * @see warm_diffuse, gooch_shading
 */
warm_color(r:real, b:real, g:real);

/**
 * @~english
 * Define cool color by its r, g, b values.
 * This color is used for <em>Gooch shading</em> effect.
 * Cool color indicates surfaces that are angled away from the light source.
 *
 * @~french
 * Définit la couleur froide pour l'effet <em>Gooch shading</em>.
 * La couleur froide met en évidence les surfaces qui ne font pas face
 * à la lumière.
 *
 * @~
 * @see cool_diffuse, gooch_shading
 */
cool_color(r:real, b:real, g:real);

/**
 * @~english
 * Define surface color by its r, g, b values.
 * This color is used for the <em>Gooch shading</em> effect.
 *
 * @~french
 * Définit la couleur de surface de l'effet <em>Gooch shading</em>.
 * @~
 * @see gooch_shading
 */
surface_color(r:real, b:real, g:real);

/**
 * @~english
 *  Apply gooch shading on current scene.
 *  It change current color (or texture) in a toon one, which is obtained in mixing
 *  colors defined by @ref warm_color, @ref cool_color and @ref surface_color
 *  according to the corresponding coefficients.
 *
 *  @note This effect can support a maximum of 8 differents lights.
 *  @see For further informations, see <a href="http://www.cs.northwestern.edu/~ago820/SIG98/abstract.html">
A Non-Photorealistic Lighting Model For Automatic Technical Illustration</a>

 * @~french
 * Active l'effet <em>Gooch shading</em>.
 * Ajoute un effet de <em>Gooch shading</em> dans la scène courante.
 *
 * Cet effet peut être utiliser pour réaliser des illustrations techniques en
 * changant la couleur des objets par un mélange des couleurs définies par
 * @ref warm_color, @ref cool_color et @ref surface_color suivant
 * l'algorithme <em>Gooch shading</em>.
 *
 * Le dégradé chaud vers froid illustre l'orientation de la face vers la lumière.
 *
 * @note Cet effet peut supporter jusqu'à 8 sources de lumières différentes.
 * @see Pour plus d'informations, voir <a href="http://www.cs.northwestern.edu/~ago820/SIG98/abstract.html">
A Non-Photorealistic Lighting Model For Automatic Technical Illustration</a>
 */
gooch_shading();


/**
* @}
*/
