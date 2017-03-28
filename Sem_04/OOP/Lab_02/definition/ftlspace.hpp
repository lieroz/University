//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_FTLSPACE_HPP
#define LAB_02_FTLSPACE_HPP

namespace ftl {
	
	namespace ftl_core {
		
		/**
		 * @brief Class encapsulating common object features.
		 */
		template <class __Tp>
		class object_traits;
		
		/**
         * @brief Class encapsulating memory allocation policy.
         */
		template <class __Tp>
		class standard_alloc_policy;
		
		/**
		 * @brief __Pl : Inherits class-strategy encapsulating memory allocation policy
		 * @see standard_alloc_policy
		 * @brief __Tr : Inherits class-strategy encapsulating common object traits.
		 * @see object_traits
		 * @brief Class encapsulating all memory operations
		 */
		template <class __Tp, class __Pl, class __Tr>
		class base_allocator;
		
		/**
         * @brief Class encapsulating most base iterator concept
         */
		template <class __Tp>
		class base_iterator;
		
		/**
 		 * @brief Inherits base_iterator
 		 * @birief Class encapsulating iterator for containers using memory dump as base.
 		 */
		template <class __Tp>
		class base_array_iterator;
		
		/**
         * @brief Class encapsulating most base container concept
         */
		template <class __Tp>
		class base_container;
		
		/**
		 * @brief Inherits base_container
         * @brief Class encapsulating most expanding container concept
         */
		template <class __Tp, class __Al>
		class expanding_container;
	} // faster than light core
	
	/**
	 * @brief Inherits ftl_core::base_array_iterator
	 * @brief Class encapsulating non-const iterator concept.
	 */
	template <class __Tp>
	class array_iterator;
	
	/**
 	 * @brief Inherits ftl_core::base_array_iterator
 	 * @brief Class encapsulating const iterator concept.
 	 */
	template <class __Tp>
	class const_array_iterator;
	
	/**
  	 * @brief Inherits ftl_core::expanding_container
  	 * @brief Class encapsulating std::vector test implementation.
 	 */
	template <class __Tp, class __Al>
	class vector;
	
	/**
     * @brief Inherits ftl_core::expanding_container
     * @brief Class encapsulating mathematical set test implementation.
  	 */
	template <class __Tp, class __Al>
	class set;
} // faster than light

#endif // LAB_02_FTLSPACE_HPP
