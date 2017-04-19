#ifndef ABSTRACT_MANAGER_HPP
#define ABSTRACT_MANAGER_HPP

class abstract_manager {
    public:
        abstract_manager() = default;
        abstract_manager(abstract_manager&) = delete;
        abstract_manager(const abstract_manager&) = delete;
        virtual ~abstract_manager() = default;
};

#endif // ABSTRACT_MANAGER_HPP
