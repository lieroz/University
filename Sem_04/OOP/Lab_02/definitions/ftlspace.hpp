//
// Created by lieroz on 17.03.17.
//

#ifndef LAB_02_FTLSPACE_HPP
#define LAB_02_FTLSPACE_HPP

#include <cstddef>
#include <iostream>

namespace ftl {
	
	namespace ftl_core {
		
		/**
 		 * @brief Inherits base_iterator
 		 * @birief Class encapsulating iterator for containers using memory dump as base.
 		 */
		template <class __Tp>
		class base_iterator;
		
		/**
         * @brief Class encapsulating most base container concept
         */
		class base_container;
		
		/**
		 * @brief Inherits base_container
         * @brief Class encapsulating most expanding container concept
         */
		template <class __Tp>
		class expanding_container;
	} // ftl_core
	
	/**
	 * @brief Inherits ftl_core::base_array_iterator
	 * @brief Class encapsulating non-const iterator concept.
	 */
	template <class __Tp>
	class set_iterator;
	
	/**
 	 * @brief Inherits ftl_core::base_array_iterator
 	 * @brief Class encapsulating const iterator concept.
 	 */
	template <class __Tp>
	class const_set_iterator;
	
	/**
     * @brief Inherits ftl_core::expanding_container
     * @brief Class encapsulating mathematical set test implementation.
  	 */
	template <class __Tp>
	class set;
} // ftl

#endif // LAB_02_FTLSPACE_HPP
