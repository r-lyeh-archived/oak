// a simple tree container
// rlyeh. mit licensed

#pragma once
#include <cassert>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

namespace oak
{
    // tree class
    // [] means read-writeable (so is <<)
    // () means read-only access

    template< typename K, typename V = int >
    class tree : public std::map< K, tree<K,V> > {

            enum { OAK_VERBOSE = false };

            typedef typename std::map< K, tree<K,V> > map;

            template< typename T >
            T zero() {
                return std::pair<T,T>().first;
            }

            template<typename T>
            T &invalid() const {
                static T t;
                return t = T(), t;
            }

            V value;
            tree *parent;

        public:

            tree() : map(), value(zero<V>()) {
                parent = this;
            }

            tree( const tree &t ) : map(), value(zero<V>()) {
                parent = this;
                operator=(t);
            }

            // tree clone

            tree &operator=( const tree &t ) {
                if( this != &t ) {
                    this->clear();
                    get() = zero<V>();
                    operator+=(t);
                }
                return *this;
            }

            // tree merge

            tree &operator+=( const tree &t ) {
                if( this != &t ) {
                    for( typename tree::const_iterator it = t.begin(), end = t.end(); it != end; ++it ) {
                        this->map::insert( *it );
                    }
                    get() = t.get();
                }
                return *this;
            }

            // tree search ; const safe find: no insertions on new searches

            const tree &at( const K &t ) const {
                typename map::const_iterator find = this->find( t );
                return find != this->end() ? find->second : invalid<tree>();
            }

            // tree insertion

            tree &insert( const K &t ) {
                map &children = *this;
                ( children[t] = children[t] ).parent = this;
                return children[t];
            }
            tree &erase( const K &t ) {
                typename map::iterator find = this->find(t);
                if( find != this->end() ) this->map::erase(t);
                return *this;
            }

            // recursive values

            V &get() {
                return value;
            }
            const V &get() const {
                return value;
            }

            template<typename other>
            tree &set( const other &t ) {
                get() = t;
                return *this;
            }
            template<typename other>
            tree &setup( const other &t ) {
                if( !is_root() ) {
                    up().set(t).setup(t);
                }
                return *this;
            }
            template<typename other>
            tree &setdown( const other &t ) {
                for( typename tree::iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    it->second.set(t).setdown( t );
                }
                return *this;
            }

            V getdown() const {
                V value = get();
                for( typename tree::const_iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    value += it->second.getdown();
                }
                return value;
            }

            // sugars

            tree &clone( const tree &t ) {
                return operator=( t );
            }
            tree &assign( const tree &t ) {
                return operator=( t );
            }

            template<typename other>
            tree &operator=( const other &t ) {
                return set(t);
            }
            template<typename other>
            tree &operator+=( const other &t ) {
                return get() += t, *this;
            }

            tree &merge( const tree &t ) {
                return operator +=( t );
            }
            tree &operator[]( const K &t ) {
                return insert( t );
            }
            const tree &operator()( const K &t ) const {
                return at( t );
            }

            bool empty( const K &t ) const { // @todo: subempty
                return this->find(t) == this->end();
            }
            bool has( const K &t ) const {
                return !empty( t );
            }

            bool operator!() const {
                return this == &invalid<tree>();
            }

            const map &children() const {
                return *this;
            }
            map &children() {
                return *this;
            }

            tree &up() {
                return *parent;
            }
            const tree &up() const {
                return *parent;
            }

            bool is_root() const {
                return parent == this;
            }
            const tree &root() const {
                if( !is_root() ) return parent->root();
                return *this;
            }
            tree &root() {
                if( !is_root() ) return parent->root();
                return *this;
            }

            // tools

            template<typename ostream>
            void print( ostream &cout = std::cout, unsigned depth = 0 ) const {
                std::string tabs( depth, '\t' );
                for( typename tree::const_iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    cout << tabs << "[" << this->size() << "] " << it->first << " (" << it->second.get() << ")";
                    if( !OAK_VERBOSE ) cout << std::endl;
                    else               cout << ".t=" << this << ",.p=" << parent << std::endl;
                    it->second.print( cout, depth + 1 );
                }
            }

            template<typename U, typename ostream>
            void print( const std::map< K, U > &tmap, ostream &cout, unsigned depth = 0 ) const {
                std::string tabs( depth, '\t' );
                for( typename tree::const_iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    cout << tabs << "[" << this->size() << "] " << tmap.find( it->first )->second << " (" << it->second.get() << ")";
                    if( !OAK_VERBOSE ) cout << std::endl;
                    else               cout << ".t=" << this << ",.p=" << parent << std::endl;
                    it->second.print( tmap, cout, depth + 1 );
                }
            }

            template<typename ostream>
            inline friend ostream &operator<<( ostream &os, const tree &self ) {
                return self.print( os ), os;
            }

            template<typename U>
            tree<U> rekey( const std::map< K, U > &map ) const {
                tree<U> utree;
                for( typename tree::const_iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    typename std::map< K, U >::const_iterator find = map.find( it->first );
                    assert( find != map.end() );
                    utree[ find->second ] += it->second.rekey( map );
                    utree[ find->second ].get() = it->second.get();
                }
                return utree;
            }
            template<typename U>
            tree<U> rekey( const std::map< U, K > &map ) const {
                // this could be faster
                tree<U> utree;
                for( typename std::map< U, K >::const_iterator it = map.begin(), end = map.end(); it != end; ++it ) {
                    typename tree::const_iterator find = this->find( it->second );
                    if( find == this->end() ) continue;
                    utree[ it->first ] += find->second.rekey( map );
                    utree[ it->first ].get() = find->second.get();
                }
                return utree;
            }

            tree collapse() const {
                tree t;
                if( this->size() == 1 ) {
                    return this->begin()->second.collapse();
                } else {
                    for( typename tree::const_iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                        t[ it->first ] += it->second.collapse();
                        t[ it->first ].get() = it->second.get();
                    }
                }
                return t;
            }

            V refresh() {
                V value = this->empty() ? get() : zero<V>();
                for( typename tree::iterator it = this->begin(), end = this->end(); it != end; ++it ) {
                    value += it->second.refresh();
                }
                return get() = value;
            }
    };
}
