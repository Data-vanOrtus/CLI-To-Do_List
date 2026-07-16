# Coding Guidelines

## general formatting

The formatting is simple.
-While there is no hard limit for line length, aim for less than 120,
 at all times, with less than 100 being optimal
 (one or two over doesnt matter)
-Readabilety should be a target to strive for.
 If, and only if, it is not apparent what your code does,
 add an explanatory comment and docs.
-DO NOT use namespaces, always use eg: std::,
 or class_name::
-Assignment, comparison and arithmetic operators should always be surrounded
 by spaces (exceptions being eg i++ and i-- or similar)
-Brackets of the () and {} variety, when not used in functions or similar
 should always be separated from their contents by whitespaces on both sides.
 Exceptions being eg: (*variable).operation
 (*variable).sub_object or similar
-(de-)reference operators should always be as such:
 var_type* name
 var_type& name
 *var_name
 &var_name
 (as applicable)
 Please do not separate them with a whitespace
-Brackets of the [] variety used for indexing or defining array length
 should NOT be seperated from their contents by whitespaces
-A tab is required as an indent for:
 Functions
 Loops (including if/else)
 Switch case:
  switch( condition ) {
    case 1:
        code
    case 2:
        code
    etc
  }

## arrays, structs, maps, templates

I do not yet have an opinion on templates
structs are initialised as such:
struct optional_name {
    data_type name = optional value;
    data_type name = optional value;#
    etc
} optional created object(-s);
Longer arrays should be created equivalently.
Shorter arrays can be created in one line.
the three values in an array representing an rgb color would fall under
this category.
maps should look something like this:
std::map<dtype1, dtype2> name = {
    { key1, value1 },
    { key2, value2 },
    etc
};

## while and for loops

while loops should have the following structure:
while ( conditions to apply )
    {
    code to be executed
}
equivalently for for loops:
for ( conditions to apply )
    {
    code to be executed
}

## functions

functions shall be written as such:
return_type function_name( parameter1,
                           parameter2,
                           etc )
    {
    code to be executed
}
Notably a function call shoul look something like this
variable = function( parameter1,
                     parameter2,
                     etc );
(Or skip the variable = when a function does not return anything)

## external libraries

don't, standart lib only
