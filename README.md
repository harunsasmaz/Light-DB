# Light-DB

LightDB is an in-memory, append-only, single-table database.

* In-memory: Database files are located in local device.

* Append-only: Only insert operation is available, no delete or update.

* Single-table: There is only a pre-defined table generated in the source code.

LightDB is a tiny clone of SQLite, which uses BTrees for fast lookups and hence insert/delete/update operations.

* If you are not familiar with Btrees, read [this tutorial](https://www.cs.cornell.edu/courses/cs3110/2012sp/recitations/rec25-B-trees/rec25.html) before starting.

<h3> Table </h3>

| <b>column</b> | <b>type</b>  |
|---------------|--------------|
| id            | integer      |
| username      | varchar(32)  |
| email         | varchar(255) |

* <b>Note that this table can be adjusted within the code. </b>

## Operations

<h3> Statements </h3>

<h4> Insert </h4>

> insert {id} {username} {email}

<h4> Select </h4>

> select

<h3> Meta-commands </h3>

<h4> Exit </h4>

> .exit

<h4> List the BTree </h4>

> .btree

<h4> List constants </h4>

> .constants


