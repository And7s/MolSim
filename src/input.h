// Copyright (c) 2005-2011 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef INPUT_HXX
#define INPUT_HXX

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3999909L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

// Begin prologue.
//
//
// End prologue.

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class input_t;
class cuboid;
class sphere;
class boundaryCondition;
class LinkedCellDomain;
class Thermostats;
class vectorF;
class vectorI;
class nonNegativeFloat;
class positiveFloat;
class positionType;
class boundaryType;

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class input_t: public ::xml_schema::type
{
  public:
  // epsilon
  // 
  typedef ::xml_schema::double_ epsilon_type;
  typedef ::xsd::cxx::tree::traits< epsilon_type, char, ::xsd::cxx::tree::schema_type::double_ > epsilon_traits;

  const epsilon_type&
  epsilon () const;

  epsilon_type&
  epsilon ();

  void
  epsilon (const epsilon_type& x);

  // sigma
  // 
  typedef ::xml_schema::double_ sigma_type;
  typedef ::xsd::cxx::tree::traits< sigma_type, char, ::xsd::cxx::tree::schema_type::double_ > sigma_traits;

  const sigma_type&
  sigma () const;

  sigma_type&
  sigma ();

  void
  sigma (const sigma_type& x);

  // base_output_file
  // 
  typedef ::xml_schema::string base_output_file_type;
  typedef ::xsd::cxx::tree::traits< base_output_file_type, char > base_output_file_traits;

  const base_output_file_type&
  base_output_file () const;

  base_output_file_type&
  base_output_file ();

  void
  base_output_file (const base_output_file_type& x);

  void
  base_output_file (::std::auto_ptr< base_output_file_type > p);

  // xvf_data_file
  // 
  typedef ::xml_schema::string xvf_data_file_type;
  typedef ::xsd::cxx::tree::traits< xvf_data_file_type, char > xvf_data_file_traits;

  const xvf_data_file_type&
  xvf_data_file () const;

  xvf_data_file_type&
  xvf_data_file ();

  void
  xvf_data_file (const xvf_data_file_type& x);

  void
  xvf_data_file (::std::auto_ptr< xvf_data_file_type > p);

  // frequency
  // 
  typedef ::xml_schema::integer frequency_type;
  typedef ::xsd::cxx::tree::traits< frequency_type, char > frequency_traits;

  const frequency_type&
  frequency () const;

  frequency_type&
  frequency ();

  void
  frequency (const frequency_type& x);

  // dimensions
  // 
  typedef ::xml_schema::positive_integer dimensions_type;
  typedef ::xsd::cxx::tree::traits< dimensions_type, char > dimensions_traits;

  const dimensions_type&
  dimensions () const;

  dimensions_type&
  dimensions ();

  void
  dimensions (const dimensions_type& x);

  // start_time
  // 
  typedef ::xml_schema::decimal start_time_type;
  typedef ::xsd::cxx::tree::traits< start_time_type, char, ::xsd::cxx::tree::schema_type::decimal > start_time_traits;

  const start_time_type&
  start_time () const;

  start_time_type&
  start_time ();

  void
  start_time (const start_time_type& x);

  // tend
  // 
  typedef ::xml_schema::decimal tend_type;
  typedef ::xsd::cxx::tree::traits< tend_type, char, ::xsd::cxx::tree::schema_type::decimal > tend_traits;

  const tend_type&
  tend () const;

  tend_type&
  tend ();

  void
  tend (const tend_type& x);

  // delta_t
  // 
  typedef ::xml_schema::float_ delta_t_type;
  typedef ::xsd::cxx::tree::traits< delta_t_type, char > delta_t_traits;

  const delta_t_type&
  delta_t () const;

  delta_t_type&
  delta_t ();

  void
  delta_t (const delta_t_type& x);

  // input_file
  // 
  typedef ::xml_schema::string input_file_type;
  typedef ::xsd::cxx::tree::traits< input_file_type, char > input_file_traits;

  const input_file_type&
  input_file () const;

  input_file_type&
  input_file ();

  void
  input_file (const input_file_type& x);

  void
  input_file (::std::auto_ptr< input_file_type > p);

  // cuboid
  // 
  typedef ::cuboid cuboid_type;
  typedef ::xsd::cxx::tree::sequence< cuboid_type > cuboid_sequence;
  typedef cuboid_sequence::iterator cuboid_iterator;
  typedef cuboid_sequence::const_iterator cuboid_const_iterator;
  typedef ::xsd::cxx::tree::traits< cuboid_type, char > cuboid_traits;

  const cuboid_sequence&
  cuboid () const;

  cuboid_sequence&
  cuboid ();

  void
  cuboid (const cuboid_sequence& s);

  // sphere
  // 
  typedef ::sphere sphere_type;
  typedef ::xsd::cxx::tree::sequence< sphere_type > sphere_sequence;
  typedef sphere_sequence::iterator sphere_iterator;
  typedef sphere_sequence::const_iterator sphere_const_iterator;
  typedef ::xsd::cxx::tree::traits< sphere_type, char > sphere_traits;

  const sphere_sequence&
  sphere () const;

  sphere_sequence&
  sphere ();

  void
  sphere (const sphere_sequence& s);

  // boundaryCondition
  // 
  typedef ::boundaryCondition boundaryCondition_type;
  typedef ::xsd::cxx::tree::sequence< boundaryCondition_type > boundaryCondition_sequence;
  typedef boundaryCondition_sequence::iterator boundaryCondition_iterator;
  typedef boundaryCondition_sequence::const_iterator boundaryCondition_const_iterator;
  typedef ::xsd::cxx::tree::traits< boundaryCondition_type, char > boundaryCondition_traits;

  const boundaryCondition_sequence&
  boundaryCondition () const;

  boundaryCondition_sequence&
  boundaryCondition ();

  void
  boundaryCondition (const boundaryCondition_sequence& s);

  // LinkedCellDomain
  // 
  typedef ::LinkedCellDomain LinkedCellDomain_type;
  typedef ::xsd::cxx::tree::traits< LinkedCellDomain_type, char > LinkedCellDomain_traits;

  const LinkedCellDomain_type&
  LinkedCellDomain () const;

  LinkedCellDomain_type&
  LinkedCellDomain ();

  void
  LinkedCellDomain (const LinkedCellDomain_type& x);

  void
  LinkedCellDomain (::std::auto_ptr< LinkedCellDomain_type > p);

  // Thermostats
  // 
  typedef ::Thermostats Thermostats_type;
  typedef ::xsd::cxx::tree::traits< Thermostats_type, char > Thermostats_traits;

  const Thermostats_type&
  Thermostats () const;

  Thermostats_type&
  Thermostats ();

  void
  Thermostats (const Thermostats_type& x);

  void
  Thermostats (::std::auto_ptr< Thermostats_type > p);

  // Constructors.
  //
  input_t (const epsilon_type&,
           const sigma_type&,
           const base_output_file_type&,
           const xvf_data_file_type&,
           const frequency_type&,
           const dimensions_type&,
           const start_time_type&,
           const tend_type&,
           const delta_t_type&,
           const input_file_type&,
           const LinkedCellDomain_type&,
           const Thermostats_type&);

  input_t (const epsilon_type&,
           const sigma_type&,
           const base_output_file_type&,
           const xvf_data_file_type&,
           const frequency_type&,
           const dimensions_type&,
           const start_time_type&,
           const tend_type&,
           const delta_t_type&,
           const input_file_type&,
           ::std::auto_ptr< LinkedCellDomain_type >&,
           ::std::auto_ptr< Thermostats_type >&);

  input_t (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  input_t (const input_t& x,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  virtual input_t*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  input_t&
  operator= (const input_t& x);

  virtual 
  ~input_t ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< epsilon_type > epsilon_;
  ::xsd::cxx::tree::one< sigma_type > sigma_;
  ::xsd::cxx::tree::one< base_output_file_type > base_output_file_;
  ::xsd::cxx::tree::one< xvf_data_file_type > xvf_data_file_;
  ::xsd::cxx::tree::one< frequency_type > frequency_;
  ::xsd::cxx::tree::one< dimensions_type > dimensions_;
  ::xsd::cxx::tree::one< start_time_type > start_time_;
  ::xsd::cxx::tree::one< tend_type > tend_;
  ::xsd::cxx::tree::one< delta_t_type > delta_t_;
  ::xsd::cxx::tree::one< input_file_type > input_file_;
  cuboid_sequence cuboid_;
  sphere_sequence sphere_;
  boundaryCondition_sequence boundaryCondition_;
  ::xsd::cxx::tree::one< LinkedCellDomain_type > LinkedCellDomain_;
  ::xsd::cxx::tree::one< Thermostats_type > Thermostats_;
};

class cuboid: public ::xml_schema::type
{
  public:
  // position
  // 
  typedef ::vectorF position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // number
  // 
  typedef ::vectorI number_type;
  typedef ::xsd::cxx::tree::traits< number_type, char > number_traits;

  const number_type&
  number () const;

  number_type&
  number ();

  void
  number (const number_type& x);

  void
  number (::std::auto_ptr< number_type > p);

  // distance
  // 
  typedef ::nonNegativeFloat distance_type;
  typedef ::xsd::cxx::tree::traits< distance_type, char > distance_traits;

  const distance_type&
  distance () const;

  distance_type&
  distance ();

  void
  distance (const distance_type& x);

  void
  distance (::std::auto_ptr< distance_type > p);

  // mass
  // 
  typedef ::nonNegativeFloat mass_type;
  typedef ::xsd::cxx::tree::traits< mass_type, char > mass_traits;

  const mass_type&
  mass () const;

  mass_type&
  mass ();

  void
  mass (const mass_type& x);

  void
  mass (::std::auto_ptr< mass_type > p);

  // velocity
  // 
  typedef ::vectorF velocity_type;
  typedef ::xsd::cxx::tree::traits< velocity_type, char > velocity_traits;

  const velocity_type&
  velocity () const;

  velocity_type&
  velocity ();

  void
  velocity (const velocity_type& x);

  void
  velocity (::std::auto_ptr< velocity_type > p);

  // Constructors.
  //
  cuboid (const position_type&,
          const number_type&,
          const distance_type&,
          const mass_type&,
          const velocity_type&);

  cuboid (::std::auto_ptr< position_type >&,
          ::std::auto_ptr< number_type >&,
          const distance_type&,
          const mass_type&,
          ::std::auto_ptr< velocity_type >&);

  cuboid (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  cuboid (const cuboid& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual cuboid*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  cuboid&
  operator= (const cuboid& x);

  virtual 
  ~cuboid ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< number_type > number_;
  ::xsd::cxx::tree::one< distance_type > distance_;
  ::xsd::cxx::tree::one< mass_type > mass_;
  ::xsd::cxx::tree::one< velocity_type > velocity_;
};

class sphere: public ::xml_schema::type
{
  public:
  // position
  // 
  typedef ::vectorF position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // radius
  // 
  typedef ::nonNegativeFloat radius_type;
  typedef ::xsd::cxx::tree::traits< radius_type, char > radius_traits;

  const radius_type&
  radius () const;

  radius_type&
  radius ();

  void
  radius (const radius_type& x);

  void
  radius (::std::auto_ptr< radius_type > p);

  // distance
  // 
  typedef ::xml_schema::float_ distance_type;
  typedef ::xsd::cxx::tree::traits< distance_type, char > distance_traits;

  const distance_type&
  distance () const;

  distance_type&
  distance ();

  void
  distance (const distance_type& x);

  // mass
  // 
  typedef ::nonNegativeFloat mass_type;
  typedef ::xsd::cxx::tree::traits< mass_type, char > mass_traits;

  const mass_type&
  mass () const;

  mass_type&
  mass ();

  void
  mass (const mass_type& x);

  void
  mass (::std::auto_ptr< mass_type > p);

  // velocity
  // 
  typedef ::vectorF velocity_type;
  typedef ::xsd::cxx::tree::traits< velocity_type, char > velocity_traits;

  const velocity_type&
  velocity () const;

  velocity_type&
  velocity ();

  void
  velocity (const velocity_type& x);

  void
  velocity (::std::auto_ptr< velocity_type > p);

  // Constructors.
  //
  sphere (const position_type&,
          const radius_type&,
          const distance_type&,
          const mass_type&,
          const velocity_type&);

  sphere (::std::auto_ptr< position_type >&,
          const radius_type&,
          const distance_type&,
          const mass_type&,
          ::std::auto_ptr< velocity_type >&);

  sphere (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  sphere (const sphere& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual sphere*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  sphere&
  operator= (const sphere& x);

  virtual 
  ~sphere ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< radius_type > radius_;
  ::xsd::cxx::tree::one< distance_type > distance_;
  ::xsd::cxx::tree::one< mass_type > mass_;
  ::xsd::cxx::tree::one< velocity_type > velocity_;
};

class boundaryCondition: public ::xml_schema::type
{
  public:
  // boundary
  // 
  typedef ::boundaryType boundary_type;
  typedef ::xsd::cxx::tree::traits< boundary_type, char > boundary_traits;

  const boundary_type&
  boundary () const;

  boundary_type&
  boundary ();

  void
  boundary (const boundary_type& x);

  void
  boundary (::std::auto_ptr< boundary_type > p);

  // position
  // 
  typedef ::positionType position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::auto_ptr< position_type > p);

  // Constructors.
  //
  boundaryCondition (const boundary_type&,
                     const position_type&);

  boundaryCondition (const ::xercesc::DOMElement& e,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  boundaryCondition (const boundaryCondition& x,
                     ::xml_schema::flags f = 0,
                     ::xml_schema::container* c = 0);

  virtual boundaryCondition*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  boundaryCondition&
  operator= (const boundaryCondition& x);

  virtual 
  ~boundaryCondition ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< boundary_type > boundary_;
  ::xsd::cxx::tree::one< position_type > position_;
};

class LinkedCellDomain: public ::xml_schema::type
{
  public:
  // dimension
  // 
  typedef ::vectorF dimension_type;
  typedef ::xsd::cxx::tree::traits< dimension_type, char > dimension_traits;

  const dimension_type&
  dimension () const;

  dimension_type&
  dimension ();

  void
  dimension (const dimension_type& x);

  void
  dimension (::std::auto_ptr< dimension_type > p);

  // cutoff
  // 
  typedef ::nonNegativeFloat cutoff_type;
  typedef ::xsd::cxx::tree::traits< cutoff_type, char > cutoff_traits;

  const cutoff_type&
  cutoff () const;

  cutoff_type&
  cutoff ();

  void
  cutoff (const cutoff_type& x);

  void
  cutoff (::std::auto_ptr< cutoff_type > p);

  // Constructors.
  //
  LinkedCellDomain (const dimension_type&,
                    const cutoff_type&);

  LinkedCellDomain (::std::auto_ptr< dimension_type >&,
                    const cutoff_type&);

  LinkedCellDomain (const ::xercesc::DOMElement& e,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  LinkedCellDomain (const LinkedCellDomain& x,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  virtual LinkedCellDomain*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  LinkedCellDomain&
  operator= (const LinkedCellDomain& x);

  virtual 
  ~LinkedCellDomain ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< dimension_type > dimension_;
  ::xsd::cxx::tree::one< cutoff_type > cutoff_;
};

class Thermostats: public ::xml_schema::type
{
  public:
  // initial_temp
  // 
  typedef ::xml_schema::decimal initial_temp_type;
  typedef ::xsd::cxx::tree::traits< initial_temp_type, char, ::xsd::cxx::tree::schema_type::decimal > initial_temp_traits;

  const initial_temp_type&
  initial_temp () const;

  initial_temp_type&
  initial_temp ();

  void
  initial_temp (const initial_temp_type& x);

  // applied_after
  // 
  typedef ::xml_schema::positive_integer applied_after_type;
  typedef ::xsd::cxx::tree::traits< applied_after_type, char > applied_after_traits;

  const applied_after_type&
  applied_after () const;

  applied_after_type&
  applied_after ();

  void
  applied_after (const applied_after_type& x);

  // delta_temp
  // 
  typedef ::positiveFloat delta_temp_type;
  typedef ::xsd::cxx::tree::traits< delta_temp_type, char > delta_temp_traits;

  const delta_temp_type&
  delta_temp () const;

  delta_temp_type&
  delta_temp ();

  void
  delta_temp (const delta_temp_type& x);

  void
  delta_temp (::std::auto_ptr< delta_temp_type > p);

  // changed_after
  // 
  typedef ::xml_schema::positive_integer changed_after_type;
  typedef ::xsd::cxx::tree::traits< changed_after_type, char > changed_after_traits;

  const changed_after_type&
  changed_after () const;

  changed_after_type&
  changed_after ();

  void
  changed_after (const changed_after_type& x);

  // target_temp
  // 
  typedef ::xml_schema::decimal target_temp_type;
  typedef ::xsd::cxx::tree::traits< target_temp_type, char, ::xsd::cxx::tree::schema_type::decimal > target_temp_traits;

  const target_temp_type&
  target_temp () const;

  target_temp_type&
  target_temp ();

  void
  target_temp (const target_temp_type& x);

  // Constructors.
  //
  Thermostats (const initial_temp_type&,
               const applied_after_type&,
               const delta_temp_type&,
               const changed_after_type&,
               const target_temp_type&);

  Thermostats (const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  Thermostats (const Thermostats& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  virtual Thermostats*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  Thermostats&
  operator= (const Thermostats& x);

  virtual 
  ~Thermostats ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< initial_temp_type > initial_temp_;
  ::xsd::cxx::tree::one< applied_after_type > applied_after_;
  ::xsd::cxx::tree::one< delta_temp_type > delta_temp_;
  ::xsd::cxx::tree::one< changed_after_type > changed_after_;
  ::xsd::cxx::tree::one< target_temp_type > target_temp_;
};

class vectorF: public ::xml_schema::type
{
  public:
  // x
  // 
  typedef ::xml_schema::decimal x_type;
  typedef ::xsd::cxx::tree::traits< x_type, char, ::xsd::cxx::tree::schema_type::decimal > x_traits;

  const x_type&
  x () const;

  x_type&
  x ();

  void
  x (const x_type& x);

  // y
  // 
  typedef ::xml_schema::decimal y_type;
  typedef ::xsd::cxx::tree::traits< y_type, char, ::xsd::cxx::tree::schema_type::decimal > y_traits;

  const y_type&
  y () const;

  y_type&
  y ();

  void
  y (const y_type& x);

  // z
  // 
  typedef ::xml_schema::decimal z_type;
  typedef ::xsd::cxx::tree::traits< z_type, char, ::xsd::cxx::tree::schema_type::decimal > z_traits;

  const z_type&
  z () const;

  z_type&
  z ();

  void
  z (const z_type& x);

  // Constructors.
  //
  vectorF (const x_type&,
           const y_type&,
           const z_type&);

  vectorF (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  vectorF (const vectorF& x,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  virtual vectorF*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  vectorF&
  operator= (const vectorF& x);

  virtual 
  ~vectorF ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< x_type > x_;
  ::xsd::cxx::tree::one< y_type > y_;
  ::xsd::cxx::tree::one< z_type > z_;
};

class vectorI: public ::xml_schema::type
{
  public:
  // x
  // 
  typedef ::xml_schema::non_negative_integer x_type;
  typedef ::xsd::cxx::tree::traits< x_type, char > x_traits;

  const x_type&
  x () const;

  x_type&
  x ();

  void
  x (const x_type& x);

  // y
  // 
  typedef ::xml_schema::non_negative_integer y_type;
  typedef ::xsd::cxx::tree::traits< y_type, char > y_traits;

  const y_type&
  y () const;

  y_type&
  y ();

  void
  y (const y_type& x);

  // z
  // 
  typedef ::xml_schema::non_negative_integer z_type;
  typedef ::xsd::cxx::tree::traits< z_type, char > z_traits;

  const z_type&
  z () const;

  z_type&
  z ();

  void
  z (const z_type& x);

  // Constructors.
  //
  vectorI (const x_type&,
           const y_type&,
           const z_type&);

  vectorI (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  vectorI (const vectorI& x,
           ::xml_schema::flags f = 0,
           ::xml_schema::container* c = 0);

  virtual vectorI*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  vectorI&
  operator= (const vectorI& x);

  virtual 
  ~vectorI ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< x_type > x_;
  ::xsd::cxx::tree::one< y_type > y_;
  ::xsd::cxx::tree::one< z_type > z_;
};

class nonNegativeFloat: public ::xsd::cxx::tree::fundamental_base< ::xml_schema::float_, char, ::xml_schema::simple_type >
{
  public:
  // Constructors.
  //
  nonNegativeFloat (const ::xml_schema::float_&);

  nonNegativeFloat (const ::xercesc::DOMElement& e,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  nonNegativeFloat (const ::xercesc::DOMAttr& a,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  nonNegativeFloat (const ::std::string& s,
                    const ::xercesc::DOMElement* e,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  nonNegativeFloat (const nonNegativeFloat& x,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  virtual nonNegativeFloat*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~nonNegativeFloat ();
};

class positiveFloat: public ::xsd::cxx::tree::fundamental_base< ::xml_schema::float_, char, ::xml_schema::simple_type >
{
  public:
  // Constructors.
  //
  positiveFloat (const ::xml_schema::float_&);

  positiveFloat (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  positiveFloat (const ::xercesc::DOMAttr& a,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  positiveFloat (const ::std::string& s,
                 const ::xercesc::DOMElement* e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  positiveFloat (const positiveFloat& x,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  virtual positiveFloat*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  virtual 
  ~positiveFloat ();
};

class positionType: public ::xml_schema::string
{
  public:
  enum value
  {
    right,
    left,
    top,
    bottom,
    front,
    back
  };

  positionType (value v);

  positionType (const char* v);

  positionType (const ::std::string& v);

  positionType (const ::xml_schema::string& v);

  positionType (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  positionType (const ::xercesc::DOMAttr& a,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  positionType (const ::std::string& s,
                const ::xercesc::DOMElement* e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  positionType (const positionType& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual positionType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  positionType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_positionType_convert ();
  }

  protected:
  value
  _xsd_positionType_convert () const;

  public:
  static const char* const _xsd_positionType_literals_[6];
  static const value _xsd_positionType_indexes_[6];
};

class boundaryType: public ::xml_schema::string
{
  public:
  enum value
  {
    outflow,
    reflecting,
    periodic
  };

  boundaryType (value v);

  boundaryType (const char* v);

  boundaryType (const ::std::string& v);

  boundaryType (const ::xml_schema::string& v);

  boundaryType (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  boundaryType (const ::xercesc::DOMAttr& a,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  boundaryType (const ::std::string& s,
                const ::xercesc::DOMElement* e,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  boundaryType (const boundaryType& x,
                ::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0);

  virtual boundaryType*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  boundaryType&
  operator= (value v);

  virtual
  operator value () const
  {
    return _xsd_boundaryType_convert ();
  }

  protected:
  value
  _xsd_boundaryType_convert () const;

  public:
  static const char* const _xsd_boundaryType_literals_[3];
  static const value _xsd_boundaryType_indexes_[3];
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::auto_ptr< ::input_t >
input (const ::std::string& uri,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (const ::std::string& uri,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (const ::std::string& uri,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       const ::std::string& id,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       const ::std::string& id,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::std::istream& is,
       const ::std::string& id,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::auto_ptr< ::input_t >
input (::xercesc::InputSource& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::xercesc::InputSource& is,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::xercesc::InputSource& is,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::auto_ptr< ::input_t >
input (const ::xercesc::DOMDocument& d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::auto_ptr< ::input_t >
input (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Begin epilogue.
//
//
// End epilogue.

#include <xsd/cxx/post.hxx>

#endif // INPUT_HXX
