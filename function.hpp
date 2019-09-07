// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef FUNCTION_MODULE
#define FUNCTION_MODULE

/**
 * @brief   
 *     Stored procedure invocation.
 * @details 
 *     Allows any C++ stored procedure to be called using one common interface.
 */
namespace function {

    /**
     * @brief 
     *     Function type.
     * @details 
     *     This type is used to represent any function type.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Resultant,
        class ...Parametric
    >
    using Functional = Resultant( Parametric... );

    /**
     * @brief         
     *     Pure abstract procedure class.
     * @details       
     *     This type is used to call any stored procedure matching the specified
     *     return and parameter types.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Resultant,
        class ...Parametric
    >
    class Procedural {

    public:

        virtual Resultant operator()( Parametric... ) const = 0;

    };

    /**
     * @brief         
     *     Object invocation class.
     * @details       
     *     This type is used to call any object.
     * @tparam Typical
     *     Type of the object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class Resultant,
        class ...Parametric
    >
    class Objective final : public Procedural< Resultant, Parametric... > {

    public:

        Objective( Typical& object ) : object( object ) {}

        Resultant operator()( Parametric... arguments ) const 
        {
            return object( arguments... );
        }

    private:

        Typical& object;  /**< Callable object reference. */

    };

    /**
     * @brief         
     *     Object method invocation class.
     * @details       
     *     This type is used to call an object method.
     * @tparam Typical
     *     Type of the object.
     * @tparam Locative
     *     Pointer to member function type.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class Locative,
        class Resultant,
        class ...Parametric
    >
    class Methodic final : public Procedural< Resultant, Parametric... > {

    public:

        Methodic( Typical& object, const Locative method ) : 
            object( object ), method( method ) 
		{
		    if (!method)
		        throw method;
		}

        Resultant operator()( Parametric... arguments ) const 
        {
            return (object.*method)( arguments... );
        }

    private:

        Typical& object; /**< User defined object reference. */

        const Locative method; /**< Member function pointer. */

    };

    /**
     * @brief         
     *     Return and parameter type deduction constant expression object.
     * @details       
     *     This null pointer constant expression object is used to specify the
     *     return and parameter types of the call to a Designate template instance.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Resultant,
        class ...Parametric
    >
    constexpr Functional< Resultant, Parametric... >* 
        Deduction = 0;

    /**
     * @brief         
     *     Designate a function as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to a function.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Resultant,
        class ...Parametric
    >
    static constexpr Objective< Resultant( Parametric... ), Resultant, Parametric... >
    Designate( 
        Functional< Resultant, Parametric... >& 
            function 
    ) {
        using Specific = Objective< Resultant( Parametric... ), Resultant, Parametric... >;
        return Specific( function );
    }

    /**
     * @brief         
     *     Designate a data object as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to a data object.
     * @tparam Typical
     *     Type of the data object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class Resultant,
        class ...Parametric
    >
    static constexpr Objective< Typical, Resultant, Parametric... >
    Designate( 
        Typical& 
            object, 
        Functional< Resultant, Parametric... >*
            deduction 
    ) {
        using Specific = Objective< Typical, Resultant, Parametric... >;
        return Specific( object );
    }

    /**
     * @brief         
     *     Designate a data object method as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to a data object method.
     * @tparam Typical
     *     Type of the data object.
     * @tparam Locative
     *     Pointer to member function type.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class Locative,
        class Resultant,
        class ...Parametric
    >
    static constexpr Methodic< Typical, Locative, Resultant, Parametric... >
    Designate( 
        Typical& 
            object, 
        const Locative 
            method, 
        Functional< Resultant, Parametric... >* 
            deduction 
    ) {
        using Specific = Methodic< Typical, Locative, Resultant, Parametric... >;
        return Specific( object, method );
    }

}

#endif
