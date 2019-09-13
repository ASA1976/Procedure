// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef PROCEDURE_MODULE
#define PROCEDURE_MODULE
#ifndef PROCEDURE_MODULE_NOSTDCPP
#include <type_traits>
#endif

/**
 * @brief   
 *     Stored procedure call system.
 * @details 
 *     Allows any C++ stored procedure to be called using one common interface.
 */
namespace procedure {

    /**
     * @brief 
     *     Function type.
     * @details 
     *     This type is used to represent any function type.  It is useful for
     *     clarity when specifying the type of an identifier.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
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
    template <class Resultant, class ...Parametric>
    class Procedural {
    public:
        virtual Resultant operator()( Parametric... ) const = 0;
    };

    /**
     * @brief         
     *     Object invocation class.
     * @details       
     *     This type is used to call any purely procedural object.
     * @tparam Typical
     *     Type of the call object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Typical, class Resultant, class ...Parametric>
    class Objective final : public Procedural<Resultant, Parametric...> {
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
     *     This type is used to call an object method.  Define the macro 
     *     PROCEDURE_MODULE_NOTHROW to prevent throwing the null member function
     *     pointer if exceptions are not supported.  Define the macro
     *     PROCEDURE_MODULE_NOSTDCPP to prevent static assertions if the 
     *     type_traits standard library header is not available.
     * @tparam Typical
     *     Type of the object.
     * @tparam MethodLocational
     *     Pointer to member function type.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class MethodLocational,
        class Resultant,
        class ...Parametric
    >
    class Methodic final : public Procedural<Resultant, Parametric...> {
#ifndef PROCEDURE_MODULE_NOSTDCPP
        static_assert(
            ::std::is_member_function_pointer< MethodLocational >::value,
            "MethodLocational:  Pointer to member function type required"
        );
#endif
    public:
        Methodic( Typical& object, const MethodLocational method ) : 
            object( object ), method( method ) 
        {
#ifndef PROCEDURE_MODULE_NOTHROW
            if (!method)
                throw method;
#endif
        }
        Resultant operator()( Parametric... arguments ) const 
        {
            return (object.*method)( arguments... );
        }
    private:
        Typical& object; /**< User defined object reference. */
        const MethodLocational method; /**< Member function pointer. */
    };

    /**
     * @brief         
     *     Return and parameter type deduction constant expression object.
     * @details       
     *     This null pointer constant expression object is used to specify the
     *     return and parameter types of the call to a Procure template instance.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
    constexpr Functional< Resultant, Parametric... >* 
    Guide = 0;

    /**
     * @brief         
     *     Specify a function as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to a function.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric >
    static constexpr Objective<Resultant( Parametric... ), Resultant, Parametric...>
    Procure( Functional<Resultant, Parametric...>& function )
    {
        using Specific = Objective<Resultant( Parametric... ), Resultant, Parametric...>;
        return Specific( function );
    }

    /**
     * @brief         
     *     Specify a data object as a procedural call object.
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
    template <class Typical, class Resultant, class ...Parametric>
    static constexpr Objective<Typical, Resultant, Parametric...>
    Procure( Typical& object, Functional<Resultant, Parametric...>* guide ) 
    {
        using Specific = Objective<Typical, Resultant, Parametric...>;
        return Specific( object );
    }

    /**
     * @brief         
     *     Specify a data object method as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to a data object member function.  Define the macro
     *     PROCEDURE_MODULE_NOSTDCPP to prevent static assertions if the 
     *     type_traits standard library header is not available.
     * @tparam Typical
     *     Type of the data object.
     * @tparam MethodLocational
     *     Pointer to member function type.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <
        class Typical,
        class MethodLocational,
        class Resultant,
        class ...Parametric
    >
    static constexpr Methodic<Typical, MethodLocational, Resultant, Parametric...>
    Procure( 
        Typical& object, 
        const MethodLocational method, 
        Functional<Resultant, Parametric...>* guide 
    ) {
#ifndef PROCEDURE_MODULE_NOSTDCPP
        using namespace std;
        static_assert(
            is_member_function_pointer< MethodLocational >::value,
            "MethodLocational:  Pointer to member function type required"
        );
#endif
        using Specific = Methodic<Typical, MethodLocational, Resultant, Parametric...>;
        return Specific( object, method );
    }

}

#endif
