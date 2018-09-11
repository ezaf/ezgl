/*  EzGL/Object.hpp
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#ifndef EZGL_OBJECT_HPP
#define EZGL_OBJECT_HPP

/** @file       EzGL/Object.hpp
 *  @brief      Object factory and Main game executor.
 */

#include "nlohmann/json.hpp"

#include <memory>
#include <string>



namespace EzGL
{

/** @brief      Object smart pointer type. */
using ObjectPtr = std::unique_ptr<class Object>;

/** @brief      Object factory and Main game executor.
 *  @details    This class is non-inheritable (final). Use components to extend
 *              the functionality of an object instead.
 */
class Object final
{
public:
    /** @brief      Initialize and run the game.
     *  @param      fileName    File name of the main json file relative to the
     *                          executable, including the file extension. A
     *                          c-string accepting version of this function
     *                          exists too, but does not receive its own
     *                          documentation subsection.
     *  @returns    `EXIT_SUCCESS` or `EXIT_FAILURE`
     */
    static int Main(std::string const &fileName);
    static int Main(char const *fileName);

    /** @brief      Object factory.
     *  @details    Created objects are automatically added to the universe.
     *              The caller gets a reference to this new object but is not
     *              responsible for its memory management.
     *  @param      objectName  Name of the object to be created. This object
     *                          name should appear in the bottom-most level
     *                          of the provided main json file.
     *  @returns    Reference to the newly created object.
     */
    static Object& Create(std::string const &objectName);

    /** @brief      Object factory.
     *  @details    Created objects are automatically added to the universe.
     *              The caller gets a reference to this new object but is not
     *              responsible for its memory management.
     *  @param      config      Starting json data for the new object.
     *  @returns    Reference to the newly created object.
     */
    static Object& Create(nlohmann::json &config);

    /** @brief      Object destroyer.
     *  @details    Removes the referenced object from the universe.
     *  @param      object      Reference to object you want to delete.
     *  @returns    Whether the object was found and deleted or not.
     */
    static bool Destroy(Object const &object);

    /** @brief      Only graphics API binding components should call this.
     *  @details    Updates all the components of all objects in the universe.
     *              Should only be called once per frame.
     */
    static void UpdateAll();

    bool operator==(Object const &other);
    bool operator!=(Object const &other);

    void init(Object &main);
    void update(Object &main);

    // One should never have to explicitly call this.
    ~Object();

    /** @brief      Modifiable object data.
     *  @details    Stores object parameters, runtime data, component
     *              information, etc. Consult the user guides for more on how
     *              the json files are parsed and loaded.
     */
    nlohmann::json data;

    /** @brief      Interactor object pointer.
     *  @details    Used in situations when two objects interact with one
     *              another. The `Collision` module, for example, sets each
     *              object's `other` pointers to the other when two objects
     *              collide. This pointer **does not** get reset at the end of
     *              each frame; it remains the same until it is overwritten.
     */
    Object const *other;

private:
    Object(nlohmann::json &config);
    Object(Object const &other) = delete;
    //Object& operator=(Object const &other) = delete;

    class Impl;
    Impl *impl;
};

}; /* namespace EzGL */



#endif /* EZGL_OBJECT_HPP */
