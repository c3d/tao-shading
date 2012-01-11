/**
 * @~english
 * @taomoduledescription{Shading, Shading}
 * Apply some shading effects. @n
 *
 * @~french
 * @taomoduledescription{Shading, Effets Shading}
 * Applique des effets de type <em>shading</em>. @n
 *
 * @~
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
 * Defines cel color by its r, g, b values.
 * @~french
 * Definit la couleur pour l'effet <em>cel shading</em>.
 * @~
 * @see cel_shading
 */
cel_color(r:real, b:real, g:real);

/**
 * @~english
 *  Apply cell shading on current scene.
 *  It change current color (or texture) in a toon one define by @ref cel_color.
 *  @see <a href="http://en.wikipedia.org/wiki/Cel-shaded_animation">Wikipedia</a>
 *
 *  @note This effect can support a maximum of 8 differents lights.
 * @~french
 * Active l'effet <em>cel shading</em>.
 * Cf. <a href="http://fr.wikipedia.org/wiki/Ombrage_de_cellulo%C3%AFd">Wikipedia</a>.
 */
cel_shading();


/**
 * @~english
 * Define warm diffuse coefficient.
 * This coefficient is used in @ref gooch_shading in order to mix the warm color define by @ref warm_color with others.
 *
 * Its default value is 0.45.
 *
 * @~french
 * Définit le coefficient de couleur chaude pour l'effet
 * <em>Gooch shading</em>.
 * Ce coefficient agit sur la façon dont la couleur chaude (@ref warm_color)
 * est mélangée aux autres couleurs. La valeur par défaut est 0.45.
 *
 * @~
 * @see warm_color, gooch_shading
 */
warm_diffuse(w:real);

/**
 * @~english
 * Define cool diffuse coefficient.
 * This coefficient is used in @ref gooch_shading in order to mix the cool color define by @ref cool_color with others.
 *
 * Its default value is 0.045.
 *
 * @~french
 * Définit le coefficient de couleur froide pour l'effet
 * <em>Gooch shading</em>.
 * Ce coefficient agit sur la façon dont la couleur froide (@ref cool_color)
 * est mélangée aux autres couleurs. La valeur par défaut est 0.045.
 *
 * @~
 * @see cool_color, gooch_shading
 */
cool_diffuse(c:real);

/**
 * @~english
 * Define warm color by its r, g, b values.
 * This color is used in @ref gooch_shading.
 *
 * @note Warm color indicates surfaces facing toward the light source.
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
 * This color is used in @ref gooch_shading.
 *
 * @note Cool color indicates surfaces that are angled away from the light source.
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
 * This color is used in @ref gooch_shading.
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
 *  @see <a href="http://marctenbosch.com/npr_shading/">Non-photorealistic Shading</a>
 *
 *  @note This effect can support a maximum of 8 differents lights.
 *
 * An example of use of Gooch Shading is described below:
 *
 * @~french
 * Active l'effet <em>Gooch shading</em>.
 * Change la couleur des objets en mélangant les couleurs définies par
 * @ref warm_color, @ref cool_color et @ref surface_color suivant
 * l'algorithme <em>Gooch shading</em>. Le dégradé chaud vers froid illustre
 * l'orientation de la face vers la lumière.
 */
gooch_shading();


/**
* @}
*/
