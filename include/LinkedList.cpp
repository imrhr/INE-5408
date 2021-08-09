#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif   /////--------

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
  }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* first = new Node(data);
    if (first == nullptr) {
        throw std::out_of_range("Lista cheia.");
    }
    first->next(head);
    head = first;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size());
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, size_t index) {
    Node* input;
    Node* prev;
    if (index > size()) {
        throw std::out_of_range("VALORINVÁLIDO");
    } else if (index == 0) {
        push_front(data);
    } else {
        input = new Node(data);
        if (input == nullptr) {
        throw std::out_of_range("VALORINVÁLIDO");
    }
    prev = head;
    for (size_t i = 0; i < index - 1; i++) {
      prev = prev->next();
    }
    input->next(prev->next());
    prev->next(input);
    size_++;
  }
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        Node* first = head;
        T out_ = first->data();
        head = first->next();
        delete first;
        size_--;
        return out_;
  }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* var;
    if (empty()) {
        push_front(data);
    } else {
        var = head;
        std::size_t pos;
    for (pos = 0; pos < size() && data > var->data(); pos++) {
      var = var->next();
    }
    insert(data, pos);
  }
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size() - 1);
}

template <typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    Node* current;
    if (index > size_ - 1) {
    throw std::out_of_range("Erro no Index");
    } else {
    current = head;
    for (size_t i = 0; i < index; i++) {
      current = current->next();
    }
    return current->data();
    }
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    T output_;
    Node* popped;
    Node* prev;
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else if (index > size() - 1) {
        throw std::out_of_range("Parâmetro inválido");
    } else if (index == 0) {
        return pop_front();
    } else {
        prev = head;
        for (int i = 0; i < static_cast<int>(index) - 1; i++) {
            prev = prev->next();
    }
    popped = prev->next();
    output_ = popped->data();
    prev->next(popped->next());
    size_--;
    delete popped;
    return output_;
  }
}

template <typename T>
void structures::LinkedList<T>::remove(const T& data) {
    std::size_t test = find(data);
    if (test != size()) {
        pop(test);
  }
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* current = head;
    std::size_t index = size();
    for (std::size_t i = 0; i < size(); i++) {
        if (current->data() == data) {
            index = i;
            break;
    }
    if (i != size()) {
      current = current->next();
    }
    }
    return index;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}
