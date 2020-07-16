# Light-DB

LightDB is an in-memory, append-only, single-table database.

* In-memory: Database files are located in local device.

* Append-only: Only insert operation is available, no delete or update.

* Single-table: There is only a pre-defined table generated in the source code.

LightDB is a tiny clone of SQLite, which uses BTrees for fast lookups and hence insert/delete/update operations.

* If you are not familiar with Btrees, read [this tutorial](https://www.cs.cornell.edu/courses/cs3110/2012sp/recitations/rec25-B-trees/rec25.html) before starting.

<h3> How Does BTree help? </h3>

BTree is one type of the balanced trees;

* It provides O(logn) search cost in the worst case.

* Insert/delete a cell that is already found is O(1).

* Re-balancing after an insert is 0(1).

* Traversing a range of values is fast! (Unlike hashmap)

  * This property allows us to keep rows sorted in database easily.

<h3> Our Hard-Coded Table </h3>

| <b>column</b> | <b>type</b>  |
|---------------|--------------|
| id            | integer      |
| username      | varchar(32)  |
| email         | varchar(255) |

* <b>Note that this table can be adjusted within the code. </b>

## Compile and Run

    make

    ./lightdb {db name}.db

<b> .db extension is not required however .db files can be easily removed by: </b>

    make cleandb

## Operations

<h3> Statements </h3>

<h4> Insert an element </h4>

> insert {id} {username} {email}

<h4> Print all rows </h4>

> select

<b> Note that, rows are printed in ascending order by id. </b>

<h3> Meta-commands </h3>

<h4> Exit from DB </h4>

> .exit

<h4> List the BTree </h4>

> .btree

<h4> List constants </h4>

> .constants

## Error Handling

LightDB sends a warning message to the prompt in the following cases:

* Unrecognized commands.

* Negative id field.

* Existing id field. ID is the primary key of the table, so it must be unique.

* Too long username field.

* Too long email field.

* Syntax error.

<h4> Next </h4>

* E-mail regex validation.
