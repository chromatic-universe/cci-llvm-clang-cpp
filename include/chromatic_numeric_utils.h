//chromatic_numeric_utils.h william k. johnson 2015
#pragma once

//c++ standard
#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <exception>
#include <vector>
#include <bitset>
#include <map>
#include <utility>
#include <stack>
#include <bitset>

//c runtime
#include <cassert>

//chromatic
#include <generic.h>

namespace chromatic_expanded_utils
{

    //forward declarations

    //enumerations


    //constants
    #define ascii_chars 256



    //types
    typedef std::map<char,unsigned long> char_count;
    typedef char_count* char_count_ptr;
    typedef std::vector<bool> v_bool;
    typedef v_bool* v_bool_ptr;
    typedef std::bitset<ascii_chars> ascii_bits;


    //immutable
    static const unsigned long char_set_sz = 256;//ascii
    static const  std::string space = " ";//ascii


    //classes
    //--------------------------------------------------------------------
    template<typename A , typename B>
    class ceu_baby_bits
    {
        //bit and stream bits manip
        public :

            //ctor
            ceu_baby_bits() {}
            //dtor
            ~ceu_baby_bits() {}

        protected :

            //attributes

        private :

            //attributes

        public :


            //services
            //------------------------------------------------------------
            static A bin_str_to_num( const std::string& bin_str )
            {

                A dw { 0 };

                try
                {
                    //upgrade
                    dw = std::bitset<sizeof( A ) * 8> ( bin_str ).to_ulong();
                }
                catch( const std::invalid_argument& ia )
                {
                    std::cerr << "invalid argument: " << ia.what() << std::endl;
                }

                return ( dw );
            }
            //------------------------------------------------------------
            static std::string num_to_bin_str( A dw )
            {o
                //template param to binary string repr
                std::string str;
	            try
	            {
		             str = std::bitset<std::numeric_limits<A>::digits> ( dw ).to_string() ;
	            }
                catch ( const std::invalid_argument& ia )
                {
	             	 std::cerr << "invalid argument: " << ia.what() << std::endl;
	            }
                return ( str );
            }
            //------------------------------------------------------------
            static ascii_bits chars_in_str( const std::string& str ,
                                            char_count_ptr cc = nullptr
                                          )
            {
                //todo - overload this for streams
                assert( cc );

                //zero container for increment , map of chars to count of chars
                std::for_each(  cc->begin() ,
                                cc->end() ,
                                [] ( std::pair<const char,unsigned long>& elem )
                                {
                                   elem.second = 0L;
                                }
                              );
                //hash for ascii chars , initialized to false
                ascii_bits a_bits;
                a_bits.reset();

                for( auto elem : str )
                {
                                 //duplicate char , this is here
                                 //so we don't do a find and increment
                                 //for values we know aren't there
                                 if( a_bits.test( elem ) == true )
                                 {
                                    auto ch_iter = cc->find( (int) elem );
                                    if( ch_iter != cc->end() )
                                    {
                                         ch_iter->second++;
                                    }
                                 }
                                 else
                                 {
                                    //set initial instance
                                    a_bits.set( elem );
                                    int val = elem;
                                    cc->insert( std::make_pair<char,unsigned long>( val , 1L ) );
                                 }
                }
                //return the bitset if caller wants
                //to use it , such as finding out quickly
                //what chars are not in the string
                return ( a_bits );

            }
            //------------------------------------------------------------
            static bool is_unique_chars_in_str( const std::string& str )
            {
                //are there any unique chars
               	bool b_ret { false };
		        ascii_bits a_bits;

		        for( auto elem : str )
		        {
		            if( a_bits.test( elem ) == true )
		            {
		            	b_ret = false;
		            	break;
		            }
		            a_bits.set( elem );
                }

        		return ( b_ret );
            }

	        //--------------------------------------------------------------------------------------
    	    static std::string reverse_words( const std::string& words , const std::string& delimiter  )
    	    {
                //use a stack to reverse words in a string
                //todo = overload this for streams
	    	    std::ostringstream ostr;
		        std::unique_ptr<std::stack<std::string> > word_stack( new std::stack<std::string> );

                safe_tokenize_t<std::stack<std::string>>( *word_stack.get() , words.c_str() , delimiter.c_str() );

	        	do
		        {
		          ostr << word_stack->top() << delimiter;
		          word_stack->pop();
		        }
		        while( word_stack->empty() == false );

		        return ( ostr.str() );
            }
    };
    //types( integral type && base )
    typedef ceu_baby_bits<int,int> baby_bits;


    //generic
    //---------------------------------------------------------------------s
    template <typename A , typename B , typename C >
    class ceu_random_manip_t
    {
        //random number hijinks
        typedef A* a_ptr;
        typedef B* b_ptr;
        typedef C* c_ptr;

        friend std::ostream& operator<< ( std::ostream& ostr , const ceu_random_manip_t&  crm )
                                                       { return ostr << "ceu_random+manip_t"; }

        public:


            //ctors
            explicit ceu_random_manip_t( A& a , B& b , C& c ) :  m_dw_seed( 0L ) ,
                                                                 m_ptr_collection(  new A( a ) ) ,
                                                                 m_ptr_distribution( new B( b ) ) ,
                                                                 m_ptr_engine( new C( c ) )
            {}

            //dtor
            virtual ~ceu_random_manip_t() {};

        protected :

            //attributes
            int m_dw_seed;


        private :

            //attributes
            std::unique_ptr<A> m_ptr_collection;//container
            std::unique_ptr<B> m_ptr_distribution;//value to numeric
            std::unique_ptr<C> m_ptr_engine;//random algorithms

            //no copy
            ceu_random_manip_t( const ceu_random_manip_t& crm );
            //no assign
            ceu_random_manip_t& operator= ( const ceu_random_manip_t& crm );

        public :

           //accessors-inspectors
           a_ptr collection() { return( m_ptr_collection.get() ); }
           b_ptr distribution() { return( m_ptr_distribution.get() ); }
           c_ptr engine() { return( m_ptr_engine.get() ); }

           //mutators


           //services
           virtual int acquire_seed()  { return ( 0 ); }
           //-------------------------------------------------------------
           virtual A shuffle_t( const A& collection ,
                                C& engine )
           {
                //caller has to seed engine
                A shuffled { collection };

                std::shuffle( shuffled.begin() , //range begin
                              shuffled.end() ,   //range end
                              engine );          //randomness

                return ( shuffled );
           }
           //-------------------------------------------------------------
           virtual void shuffle_t()
           {
               std::shuffle(  collection()->begin() , //range begin
                              collection()->end() ,   //range end
                              *engine() );             //randomness
           }
           //-------------------------------------------------------------
          void  gen_random_init_t( A& collection ,
                                   B& distribution ,
                                   C& engine
                                 )
          {
                //caller has to seed engine
                //
                //number of generated elements
                //is sizeof collection
                for( auto& elem : collection )
                {
                    elem = distribution( engine  );
                }

          }
           //-------------------------------------------------------------
          void  gen_random_init_t()
          {

                //caller has to seed engine
                //
                //number of generated elements
                //is sizeof collection
                for( auto& elem : collection() )
                {
                    elem = (*distribution() ) ( engine() );
                }
          }

    };
    //types
    typedef ceu_random_manip_t<std::vector<int> ,
                              std::uniform_int_distribution<int> ,
                              std::default_random_engine> random_default_manip;
    typedef ceu_random_manip_t<std::vector<double> ,
                              std::uniform_real_distribution<double> ,
                              std::default_random_engine> random_float_manip;


    //immutable


}
namespace ceu = chromatic_expanded_utils;

