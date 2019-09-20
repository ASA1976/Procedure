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
 *     This includes functions, lambdas, call operators on user defined types
 *     as well as member functions with object context.  **When using the
 *     comparable classes without run-time type information (RTTI) support,
 *     comparison will only work if each unique stored procedure site is only 
 *     represented by one procedural object instance**.  With RTTI support there
 *     can be many procedural instances for each stored procedure, where the
 *     object address spaces of the stored procedures are compared directly.
 */
namespace procedure {

    /**
     * @brief 
     *     Proper function type.
     * @details 
     *     This type is used to represent any function type.  It is useful for
     *     clarity when specifying the type of an identifier, as it forces the
     *     identifier to appear last.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
    using Functional = Resultant( Parametric... );

    /**
     * @brief         
     *     Abstract procedural base class.
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
    class Procedural {

    public:

        /**
         * @brief
         *     Pure virtual call operator.
         * @details
         *     This operator must be implemented by classes which are derived
         *     from this class.
         */
        virtual Resultant operator()( Parametric... ) const = 0;

    };

    /**
     * @brief         
     *     Abstract procedural base class.
     * @details       
     *     This type is used to call or compare stored procedures matching the 
     *     specified return and parameter types
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Resultant, class ...Parametric>
    class ComparablyProcedural : public Procedural< Resultant, Parametric... > {

    public:

        /**
         * @brief
         *     Base procedural type template instance alias.
         */
        using BaseProcedural = Procedural< Resultant, Parametric... >;

        /** 
         * @brief         
         *     Pure virtual equal to operator.
         * @details       
         *     This operator must be implemented by classes which are derived 
         *     from this class.
         */
        virtual bool operator==( const BaseProcedural& ) const = 0;

        /** 
         * @brief         
         *     Not equal to operator implementation.
         * @details       
         *     This operator calls the equal to operator and inverts it's 
         *     return value.
         * @param[in] relative
         *     Procedural object to be compared not equal to.
         * @return
         *     The inverse of the equal to operator return value.
         */
        constexpr bool operator!=( const BaseProcedural& relative )
        {
            using SameProcedural = ComparablyProcedural< Resultant, Parametric... >;
            return !SameProcedural::operator==( relative );
        }

    };

    /**
     * @brief         
     *     Base class for any callable object, which excludes member functions.
     * @details       
     *     This type is used to store a reference to any callable object.
     * @tparam Typical
     *     Type of the callable object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Typical, class Resultant, class ...Parametric>
    class Objective {

    public:

        /**
         * @brief
         *     Same objective type template instance alias.
         */
        using SameObjective = Objective< Typical, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Equal to operator implementation specific to this class.
         * @details       
         *     This operator compares the addresses of the callable objects.
         * @param[in] relative
         *     Same objective type instance to be compared equal to.
         * @return
         *     True only if both reference the same object.
         */
        constexpr bool operator==( const SameObjective& relative ) const
        {
            return &object == &relative.object;
        }

        /** 
         * @brief         
         *     Not equal to operator implementation specific to this class.
         * @details       
         *     This operator compares the addresses of the callable objects.
         * @param[in] relative
         *     Same objective type instance to be compared not equal to.
         * @return
         *     False only if both reference the same object.
         */
        constexpr bool operator!=( const SameObjective& relative ) const
        {
            return !SameObjective::operator==( relative );
        }

    protected:

        /** 
         * @brief         
         *     Construct a callable object reference.
         * @details       
         *     The resulting instance will only reference the specified object.
         * @param[in] object
         *     The callable object which will be called by reference.
         */
        constexpr Objective( Typical& object ) : object( object ) {}

        Typical& object;  /**< Callable object reference. */

    };

    /**
     * @brief         
     *     Class for calling any callable object.
     * @details       
     *     This type is used to call any callable object.
     * @tparam Typical
     *     Type of the callable object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Typical, class Resultant, class ...Parametric>
    class SimplyObjective : 
        public Procedural< Resultant, Parametric... >,
        public Objective< Typical, Resultant, Parametric... >
    {

    public:

        /**
         * @brief 
         *     Base objective type template instance alias.
         */
        using BaseObjective = Objective< Typical, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Construct a callable object reference.
         * @details       
         *     The resulting instance will only reference the specified object.
         * @param[in] object
         *     The procedural call object which will be called by reference.
         */
        constexpr SimplyObjective( Typical& object ) :
            BaseObjective( object ) {}

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
            return this->object( arguments... );
        }

    };

    /**
     * @brief         
     *     Class for calling or comparing any callable object.
     * @details       
     *     This type is used to call or compare any callable object.
     * @tparam Typical
     *     Type of the callable object.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     */
    template <class Typical, class Resultant, class ...Parametric>
    class ComparablyObjective : 
        public ComparablyProcedural< Resultant, Parametric... >,
        public Objective< Typical, Resultant, Parametric... >
    {

    public:

        /**
         * @brief 
         *     Base procedural type template instance alias.
         */
        using BaseProcedural = Procedural< Resultant, Parametric... >;

        /**
         * @brief 
         *     Base objective type template instance alias.
         */
        using BaseObjective = Objective< Typical, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Construct a callable object reference.
         * @details       
         *     The resulting instance will only reference the specified object.
         * @param[in] object
         *     The procedural call object which will be called by reference.
         */
        constexpr ComparablyObjective( Typical& object ) :
            BaseObjective( object ) {}

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
            return this->object( arguments... );
        }

        /** 
         * @brief         
         *     ComparablyProcedural equal to operator.
         * @details       
         *     Implements the procedural equal to operator.  If the macro 
         *     PROCEDURE_MODULE_NORTTI is not defined, this operator uses a 
         *     dynamic cast and if relative is not of the same base objective
         *     class it returns false.  If relative is of the same base 
         *     objective class it compares their object member addresses and 
         *     returns the result.  If the macro PROCEDURE_MODULE_NORTTI is 
         *     defined, compares the address of this to the address of relative
         *     and only returns true if they are  equal.  Do not create more 
         *     than one objective instance per unique callable object address 
         *     if the equal to operator will be in use without RTTI available.
         * @param[in] relative
         *     Relative procedural instance to compare equality with.
         * @return
         *     True only under conditions described in details section.
         */
        bool operator==( const BaseProcedural& relative ) const 
        {
#ifndef PROCEDURE_MODULE_NORTTI
            const BaseObjective* same = dynamic_cast<const BaseObjective*>(&relative);
            if (!same) return false;
            return BaseObjective::operator==( *same );
#else
            return &relative == this;
#endif
        }

    };

    /**
     * @brief         
     *     Base class for any callable object member function.
     * @details       
     *     This type is used to store a reference to a callable object and 
     *     pointer to member function. Define the macro 
     *     PROCEDURE_MODULE_NOTHROW to prevent throwing the null member 
     *     function pointer.  Define the macro PROCEDURE_MODULE_NOSTDCPP to 
     *     prevent static assertions using the type_traits standard library 
     *     header.
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
    class Methodic {

#ifndef PROCEDURE_MODULE_NOSTDCPP
        static_assert(
            ::std::is_member_function_pointer< MethodLocational >::value,
            "MethodLocational: Pointer to member function type required"
        );
#endif

    public:

        /**
         * @brief 
         *     Same methodic type template instance alias.
         */
        using SameMethodic = Methodic< Typical, MethodLocational, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Equal to operator implementation specific to this class.
         * @details       
         *     This operator compares the addresses of the objects and methods.
         * @param[in] relative
         *     Same methodic type instance to be compared equal to.
         * @return
         *     True only if both reference the same object and member function.
         */
        constexpr bool operator==( const SameMethodic& relative ) const
        {
            return &object == &relative.object && method == relative.method;
        }

        /** 
         * @brief         
         *     Not equal to operator implementation specific to this class.
         * @details       
         *     This operator compares the addresses of the objects and methods.
         * @param[in] relative
         *     Same objective instance to be compared not equal to.
         * @return
         *     False only if both reference the same object and member function.
         */
        constexpr bool operator!=( const SameMethodic& relative ) const
        {
            return !SameMethodic::operator==( relative );
        }


    protected:

        /** 
         * @brief         
         *     Construct a callable object member function reference.
         * @details       
         *     The resulting instance will only reference the specified object
         *     member function.  Define the macro PROCEDURE_MODULE_NOTHROW to 
         *     prevent throwing the null member function pointer.
         * @param[in] object
         *     Reference to the object whose member will be called.
         * @param[in] method
         *     Pointer to the member function which will be called.
         */
        constexpr Methodic( Typical& object, const MethodLocational method ) : 
            object( object ), method( method ) 
        {
#ifndef PROCEDURE_MODULE_NOTHROW
            if (!method)
                throw method;
#endif
        }

        Typical& object; /**< Object reference. */

        const MethodLocational method; /**< Callable member function pointer. */

    };

    /**
     * @brief         
     *     Class for calling any callable object member function.
     * @details       
     *     This type is used to call any callable object member function.
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
    class SimplyMethodic : 
        public Procedural< Resultant, Parametric... >,
        public Methodic< Typical, MethodLocational, Resultant, Parametric... >
    {

    public:

        /**
         * @brief 
         *     Base methodic type template instance alias.
         */
        using BaseMethodic = Methodic< Typical, MethodLocational, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Construct a callable object member function reference.
         * @details       
         *     The resulting instance will only reference the specified object
         *     and member function pointer location.
         * @param[in] object
         *     The object which the member function will reference.
         * @param[in] method
         *     The member function pointer location.
         */
        constexpr SimplyMethodic( Typical& object, const MethodLocational method ) :
            BaseMethodic( object, method ) {}

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
            return (this->object.*this->method)( arguments... );
        }

    };

    /**
     * @brief         
     *     Class for calling or comparing any callable object member function.
     * @details       
     *     This type is used to call or compare any callable object member 
     *     function.
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
    class ComparablyMethodic : 
        public ComparablyProcedural< Resultant, Parametric... >,
        public Methodic< Typical, MethodLocational, Resultant, Parametric... >
    {

    public:

        /**
         * @brief 
         *     Base procedural type template instance alias.
         */
        using BaseProcedural = Procedural< Resultant, Parametric... >;

        /**
         * @brief 
         *     Base methodic type template instance alias.
         */
        using BaseMethodic = Methodic< Typical, MethodLocational, Resultant, Parametric... >;

        /** 
         * @brief         
         *     Construct a callable object member function reference.
         * @details       
         *     The resulting instance will only reference the specified object
         *     and member function pointer location.
         * @param[in] object
         *     The object which the member function will reference.
         * @param[in] method
         *     The member function pointer location.
         */
        constexpr ComparablyMethodic( Typical& object, const MethodLocational method ) :
            BaseMethodic( object, method ) {}

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
            return (this->object.*this->method)( arguments... );
        }

        /** 
         * @brief         
         *     ComparablyProcedural equal to operator.
         * @details       
         *     Implements the procedural equal to operator.  If the macro 
         *     PROCEDURE_MODULE_NORTTI is not defined, this operator uses a 
         *     dynamic cast and if relative is not of the same base methodic
         *     class it returns false.  If relative is of the same base 
         *     methodic class it compares their object and method addresses and 
         *     returns the result.  If the macro PROCEDURE_MODULE_NORTTI is 
         *     defined, compares this to the address of relative and only 
         *     returns true if they are  equal.  Do not create more than one 
         *     methodic instance per unique callable object address if the equal
         *     to operator will be in use without RTTI available.
         * @param[in] relative
         *     Relative procedural instance to compare equality with.
         * @return
         *     True only under conditions described in details section.
         */
        bool operator==( const BaseProcedural& relative ) const 
        {
#ifndef PROCEDURE_MODULE_NORTTI
            const BaseMethodic* same = dynamic_cast<const BaseMethodic*>(&relative);
            if (!same) return false;
            return BaseMethodic::operator==( *same );
#else
            return &relative == this;
#endif
        }

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
     *     This function template is used to create a simple representation of a 
     *     procedural call to a function.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     * @param[in] function
     *     Reference to the function which will be called.
     * @return
     *     Procedural object which references function.
     */
    template <class Resultant, class ...Parametric >
    static constexpr SimplyObjective< Resultant( Parametric... ), Resultant, Parametric... >
    Procure( Functional< Resultant, Parametric... >& function )
    {
        using Specific = SimplyObjective< Resultant( Parametric... ), Resultant, Parametric... >;
        return Specific( function );
    }

    /**
     * @brief         
     *     Specify a callable object as a procedural call object.
     * @details       
     *     This function template is used to create a simple representation of a 
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
    static constexpr SimplyObjective< Typical, Resultant, Parametric... >
    Procure( Typical& object, Functional< Resultant, Parametric... >* guide ) 
    {
        using Specific = SimplyObjective< Typical, Resultant, Parametric... >;
        return Specific( object );
    }

    /**
     * @brief         
     *     Specify an object member function as a procedural call object.
     * @details       
     *     This function template is used to create a simple representation of a 
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
    static constexpr SimplyMethodic< Typical, MethodLocational, Resultant, Parametric... >
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
        using Specific = SimplyMethodic< Typical, MethodLocational, Resultant, Parametric... >;
        return Specific( object, method );
    }

    /**
     * @brief         
     *     Specify a function as a procedural call object.
     * @details       
     *     This function template is used to create a comparable representation
     *     of a procedural call to a function.
     * @tparam Resultant
     *     Return type of the call.
     * @tparam ...Parametric
     *     Parameter pack which represents the parameter types of the call.
     * @param[in] function
     *     Reference to the function which will be called.
     */
    template <class Resultant, class ...Parametric >
    static constexpr ComparablyObjective< Resultant( Parametric... ), Resultant, Parametric... >
    ProcureComparably( Functional< Resultant, Parametric... >& function )
    {
        using Specific = ComparablyObjective< Resultant( Parametric... ), Resultant, Parametric... >;
        return Specific( function );
    }

    /**
     * @brief         
     *     Specify a callable object as a procedural call object.
     * @details       
     *     This function template is used to create a comparable representation
     *     of a procedural call to any callable object.  This overload is used 
     *     for lambda objects and user defined class call operator objects.  It
     *     can also be used with function types to specify rather than deduce 
     *     the return and parameter types.
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
    static constexpr ComparablyObjective< Typical, Resultant, Parametric... >
    ProcureComparably( Typical& object, Functional< Resultant, Parametric... >* guide ) 
    {
        using Specific = ComparablyObjective< Typical, Resultant, Parametric... >;
        return Specific( object );
    }

    /**
     * @brief         
     *     Specify an object member function as a procedural call object.
     * @details       
     *     This function template is used to create a comparable representation
     *     of a procedural call to an object member function.  Define the macro
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
    static constexpr ComparablyMethodic< Typical, MethodLocational, Resultant, Parametric... >
    ProcureComparably( 
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
        using Specific = ComparablyMethodic< Typical, MethodLocational, Resultant, Parametric... >;
        return Specific( object, method );
    }

}

#endif
