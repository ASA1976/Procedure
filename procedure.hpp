// © 2019 Aaron Sami Abassi
// Licensed under the Academic Free License version 3.0
#ifndef PROCEDURE_MODULE
#define PROCEDURE_MODULE
#ifndef PROCEDURE_MODULE_NOSTDCPP
#include <type_traits>
#endif

/**
 * @brief   
 *     Universal C++ stored procedure call system.
 * @details 
 *     Allows any C++ stored procedure to be called using one common interface.
 *     This system is solely designed to be a rapid system for call site 
 *     acquisition and invocation.  Type erasure and call object duplication can
 *     both be addressed using **instances of a pointer** to a Procedural type 
 *     template instance.
 */
namespace procedure {

    /**
     * @brief 
     *     Proper function type.
     * @details 
     *     This type is used to represent any function type.  It is useful for
     *     clarity when specifying the type of an identifier as in *select*
     *     portions of this source code.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
    using Functional = Resultant( Parametric... );

    /**
     * @brief         
     *     Pure abstract procedural base class.
     * @details       
     *     This type is used to call any stored procedure matching the specified
     *     return and parameter types, using the sole virtual call operator 
     *     member.  Only references and pointers to this type are useful.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
    struct Procedural {

        /** 
         * @brief         
         *     Pure virtual call operator used to call the stored procedure.
         * @details       
         *     This operator must be implemented by classes which are derived 
         *     from this class.
         */
        virtual Resultant operator()( Parametric... ) const = 0;

    };

    /**
     * @brief         
     *     Procedural class derivative for callable C++ objects.
     * @details       
     *     This type is used to call any purely procedural object by reference.
     *     Examples include traditional C style functions, lambdas and user 
     *     defined types which overload the call operator.
     * @tparam Typical
     *     Type of the callable object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Typical, class Resultant, class ...Parametric>
    class Objective final : public Procedural< Resultant, Parametric... > {

    public:

        /** 
         * @brief         
         *     Construct a procedural object reference.
         * @details       
         *     The resulting instance will only reference the specified object.
         * @param[in] object
         *     The procedural call object which will be called by reference.
         */
        Objective( Typical& object ) : object( object ) {}

        /** 
         * @brief         
         *     Procedural object call operator.
         * @details       
         *     Implements the procedural call operator by calling the object
         *     by reference and returning it's result to the calling context.
         * @param[in] ...arguments
         *     Argument pack which is expanded.
         * @return
         *     The return result of the call.
         */
        Resultant operator()( Parametric... arguments ) const 
        {
            return object( arguments... );
        }

    private:

        Typical& object;  /**< Callable object reference. */

    };

    /**
     * @brief         
     *     Procedural class derivative for object member functions.
     * @details       
     *     This type is used to call any object member function by reference.
     *     Define the macro PROCEDURE_MODULE_NOTHROW to prevent throwing the
     *     null member function pointer.  Define the macro 
     *     PROCEDURE_MODULE_NOSTDCPP to prevent static assertions if 
     *     the type_traits standard library header is not available.
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
    class Methodic final : public Procedural< Resultant, Parametric... > {
#ifndef PROCEDURE_MODULE_NOSTDCPP
        static_assert(
            ::std::is_member_function_pointer< MethodLocational >::value,
            "MethodLocational: Pointer to member function type required"
        );
#endif

    public:

        /** 
         * @brief         
         *     Construct a procedural object member function reference.
         * @details       
         *     The resulting instance will only reference the specified object
         *     and member function pointer location.
         * @param[in] object
         *     The object which the member function will reference.
         * @param[in] method
         *     The member function pointer location.
         */
        Methodic( Typical& object, const MethodLocational method ) : 
            object( object ), method( method ) 
        {
#ifndef PROCEDURE_MODULE_NOTHROW
            if (!method)
                throw method;
#endif
        }

        /** 
         * @brief         
         *     Procedural object member function call operator.
         * @details       
         *     Implements the procedural call operator by calling the object
         *     member function and returning it's result to the calling context.
         * @param[in] ...arguments
         *     Argument pack which is expanded.
         * @return
         *     The return result of the call.
         */
        Resultant operator()( Parametric... arguments ) const 
        {
            return (object.*method)( arguments... );
        }

    private:

        Typical& object; /**< Object reference. */

        const MethodLocational method; /**< Callable member function pointer. */

    };

    /**
     * @brief         
     *     Explicitly specifies a call return and parameter type expectation.
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
     * @param[in] function
     *     Reference to the function which will be called.
     */
    template <class Resultant, class ...Parametric >
    static constexpr Objective< Resultant( Parametric... ), Resultant, Parametric... >
    Procure( Functional< Resultant, Parametric... >& function )
    {
        using Specific = Objective< Resultant( Parametric... ), Resultant, Parametric... >;
        return Specific( function );
    }

    /**
     * @brief         
     *     Specify a callable object as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to any callable object.  This overload is used for 
     *     lambda objects and user defined class call operator objects.  It can
     *     also be used with function types to specify rather than deduce the 
     *     return and parameter types.
     * @tparam Typical
     *     Type of the object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     * @param[in] object
     *     Reference to the object which will be called.
     * @param[in] guide
     *     Used for template argument deduction, value is ignored.
     */
    template <class Typical, class Resultant, class ...Parametric>
    static constexpr Objective< Typical, Resultant, Parametric... >
    Procure( Typical& object, Functional< Resultant, Parametric... >* guide ) 
    {
        using Specific = Objective< Typical, Resultant, Parametric... >;
        return Specific( object );
    }

    /**
     * @brief         
     *     Specify an object member function as a procedural call object.
     * @details       
     *     This function template is used to create a representation of a 
     *     procedural call to an object member function.  Define the macro
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
     * @param[in] object
     *     Reference to the object for the member function call.
     * @param[in] method
     *     Pointer to the member function which will be called.
     * @param[in] guide
     *     Used for template argument deduction, value is ignored.
     */
    template <
        class Typical,
        class MethodLocational,
        class Resultant,
        class ...Parametric
    >
    static constexpr Methodic< Typical, MethodLocational, Resultant, Parametric... >
    Procure( 
        Typical& object, 
        const MethodLocational method, 
        Functional< Resultant, Parametric... >* guide 
    ) {
#ifndef PROCEDURE_MODULE_NOSTDCPP
        using namespace std;
        static_assert(
            is_member_function_pointer< MethodLocational >::value,
            "MethodLocational: Pointer to member function type required"
        );
#endif
        using Specific = Methodic< Typical, MethodLocational, Resultant, Parametric... >;
        return Specific( object, method );
    }

}

#endif
