module; // DataStruct-DLList.ixx

#include "ds-mod-preheader.h"

export module DataStruct:List;

import std;

import :Iterator;
import :Print;

namespace ds {
	// Node
	template <typename T>
	struct SLLNode {
		using value_type = T;
		T data;
		SLLNode* next;
	}; // singly linked list node
	
	template <typename T>
	struct DLLNode {
		using value_type = T;
		T data;
		DLLNode* next;
		DLLNode* prev;
	}; // doubly linked list node


	// DLList
	export template <typename T>
	_DS_Container class DLList : public Printable<DLLNode<T>> {
	public:
		using Node = DLLNode<T>;

		DLList() : m_sentinel(new Node{ T{} }), m_size(0) {
			m_sentinel->next = m_sentinel;
			m_sentinel->prev = m_sentinel;
		}
		DLList(std::initializer_list<T> const& il) : DLList() {
			for (auto const& e : il)
				push_back(e);
		}
		DLList(DLList const& other) : DLList() {
			for (auto const& e : other)
				push_back(e.data);
		}
		DLList(DLList&& other) noexcept :
				m_sentinel(std::exchange(other.m_sentinel, new Node{ T{} })),
				m_size(std::exchange(other.m_size, 0)) {
			other.m_sentinel->next = other.m_sentinel;
			other.m_sentinel->prev = other.m_sentinel;
		}
		~DLList() {
			clear();
			delete m_sentinel;
		}

		func operator=(DLList const& other) -> DLList& {
			if (this == &other) return *this;
			clear();
			for (auto const& e : other)
				push_back(e.data);
			return *this;
		}
		func operator=(DLList&& other) noexcept -> DLList& {
			if (this == &other) return *this;
			clear();
			std::swap(m_sentinel, other.m_sentinel);
			std::swap(m_size, other.m_size);
			return *this;
		}

		func push_back(T const& data)	-> void {
			Node* temp = new Node{ data,
				/* next */ m_sentinel,
				/* prev */ m_sentinel->prev
			};
			m_sentinel->prev->next = temp;
			m_sentinel->prev = temp;
			++m_size;
		}

		func push_front(T const& data)	-> void {
			Node* temp = new Node{ data,
				/* next */ m_sentinel->next,
				/* prev */ m_sentinel
			};
			m_sentinel->next->prev = temp;
			m_sentinel->next = temp;
			++m_size;
		}

		func pop_back()					-> void {
			if (empty()) return;
			Node* temp = m_sentinel->prev;
			m_sentinel->prev = temp->prev;
			temp->prev->next = m_sentinel;
			delete temp;
			--m_size;
		}

		func pop_front()				-> void {
			if (empty()) return;
			Node* temp = m_sentinel->next;
			m_sentinel->next = temp->next;
			temp->next->prev = m_sentinel;
			delete temp;
			--m_size;
		}

		func insert_at(size_t pos, T const& data) -> void {
			if (pos == 0) {
				push_front(data);
				return;
			}
			if (pos == m_size) {
				push_back(data);
				return;
			}
			Node* temp = m_sentinel;
			for (size_t i = 0; i < pos; ++i)
				temp = temp->next;
			Node* new_node = new Node{ data,
				/* next */ temp->next,
				/* prev */ temp };
			temp->next->prev = new_node;
			temp->next = new_node;
			++m_size;
		}

		func insert_after(Node* node, T const& data) -> void {
			if (!node) return;
			Node* new_node = new Node{ data,
				/* next */ node->next,
				/* prev */ node };
			node->next->prev = new_node;
			node->next = new_node;
			++m_size;
		}

		func insert_after_find(T const& find_data, T const& data) -> void {
			Node* temp = find(find_data);
			if (!temp) return;
			insert_after(temp, data);
		}

		func erase_at(size_t pos)		-> void {
			if (pos == 0) {
				pop_front();
				return;
			}
			if (pos == m_size - 1) {
				pop_back();
				return;
			}
			Node* temp = m_sentinel;
			for (size_t i = 0; i < pos; ++i)
				temp = temp->next;
			Node* del_node = temp->next;
			temp->next = del_node->next;
			del_node->next->prev = temp;
			delete del_node;
			--m_size;
		}

		func erase(Node* node)			-> void {
			if (!node) return;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
			--m_size;
		}

		func erase_find(T const& data)	-> void {
			Node* temp = find(data);
			if (!temp) return;
			erase(temp);
		}

		func clear()					-> void {
			Node* temp = m_sentinel->next;
			while (temp != m_sentinel) {
				Node* next = temp->next;
				delete temp;
				temp = next;
			}
			m_sentinel->next = m_sentinel;
			m_sentinel->prev = m_sentinel;
			m_size = 0;
		}

		func back()			  -> T&		  { return m_sentinel->prev->data; }
		func back()  nomodify -> T const& { return m_sentinel->prev->data; }

		func front()		  -> T&		  { return m_sentinel->next->data; }
		func front() nomodify -> T const& { return m_sentinel->next->data; }

		func find(T const& data)			-> Node* {
			Node* temp = m_sentinel->next;
			while (temp != m_sentinel && temp->data != data)
				temp = temp->next;
			return temp == m_sentinel ? nullptr : temp;
		}
		func find(T const& data) nomodify	-> Node const* {
			Node* temp = m_sentinel->next;
			while (temp != m_sentinel && temp->data != data)
				temp = temp->next;
			return temp == m_sentinel ? nullptr : temp;
		}

		func size()	 nomodify -> size_t { return m_size; }

		func empty() nomodify -> bool	{ return m_size == 0; }

	private:
		Node* m_sentinel;

		size_t m_size;

		func __begin_ptr()			-> Node*		override { return m_sentinel->next; }
		func __end_ptr()			-> Node*		override { return m_sentinel; }
		func __begin_ptr() nomodify -> Node const*  override { return m_sentinel->next; }
		func __end_ptr()   nomodify -> Node const*  override { return m_sentinel; }

	}; // class DLList

} // namespace ds