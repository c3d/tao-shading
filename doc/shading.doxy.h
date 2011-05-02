/**
 * @defgroup Shading Shading
 * @ingroup Modules
 *
 * Apply some shading effects.
 *
 * This module allows you to add to your scene some nice shading effects.
 * For instance,
 * @include shading.ddd
 *
 * @image html shading.png "Output of shading.ddd"
 * @{
 */

/**
 * Define cell color by its r, g, b values.
 * This color is used in @ref cel_shading.
 */
cel_color(r:real, b:real, g:real);

/**
 *  Apply cell shading on current scene.
 *  It change current color (or texture) in a toon one define by @ref cel_color.
 *  @see <a href="http://en.wikipedia.org/wiki/Cel-shaded_animation">Wikipedia</a>
 *
 *  @note This effect support only light zero.
 */
cel_shading();


/**
 * Define warm diffuse coefficient.
 * This coefficient is used in @ref gooch_shading in order to mix the warm color define by @ref warm_color with others.
 *
 * Its default value is 0.45.
 */
warm_diffuse(w:real);

/**
 * Define cool diffuse coefficient.
 * This coefficient is used in @ref gooch_shading in order to mix the cool color define by @ref cool_color with others.
 *
 * Its default value is 0.045.
 */
cool_diffuse(c:real);

/**
 * Define warm color by its r, g, b values.
 * This color is used in @ref gooch_shading .
 */
warm_color(r:real, b:real, g:real);

/**
 * Define cool color by its r, g, b values.
 * This color is used in @ref gooch_shading.
 */
cool_color(r:real, b:real, g:real);

/**
 * Define surface color by its r, g, b values.
 * This color is used in @ref gooch_shading.
 */
surface_color(r:real, b:real, g:real);


/**
 *  Apply gooch shading on current scene.
 *  It change current color (or texture) in a toon one, which is obtained in mixing
 *  colors defined by @ref warm_color, @ref cool_color and @ref surface_color
 *  according to the corresponding coefficients.
 *  @see <a href="http://marctenbosch.com/npr_shading/">Non-photorealistic Shading</a>
 *
 *  @note This effect support only light zero.
 */
gooch_shading();


/**
* @}
*/
