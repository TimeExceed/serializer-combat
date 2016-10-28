# serializer-combat
Comparison between several serializers in C++.

We have following candidates:
* [Avro-1.8](http://avro.apache.org/docs/1.8.1/)
* ProtoBuf-2 (under construction)
* ProtoBuf-3 (under construction)
* Msgpack (under construction)
* Thrift (under construction)
* FlatBuffers (under construction)
* Cap'n'Proto (under construction)
* RapidJson (under construction)

## General

|                   | Avro    |
| ---               | ----    |
| Sponsor           | Hadoop  |
| Format spec       | Yes     |
| Plain-text format | JSON    |
| Binary format     | Yes     |
| Code generation   | Yes     |
| Handshaking       | Yes     |
| Dynamic typing    | Yes     |
| Message framing   | Yes     |

* The purpose of the handshake is to ensure that the client and the server have each other's protocol definition, so that the client can correctly deserialize responses, and the server can correctly deserialize requests.
* Dynamic typing means the reader does not need any predefined schema to read any valid messages.
* Message framing means the reader and the writer does not necessarily read from/write to a single consecutive buffer.

## Language Support

|         | Avro |
| ---     | ---- |
| C       | Yes  |
| C++     | 98   |
| JAVA    | Yes  |
| C#      | Yes  |
| Python  | 2/3  |
| Node.js | Yes  |
| PHP     | No   |
| Ruby    | Yes  |
| Go      | No   |

## Data Types

### Primitive types

|         | Avro          |
| ---     | ----          |
| Integer | 32/64         |
| Float   | single/double |
| String  | UTF-8         |
| Binary  | dynamic/fixed |

### Complex types

|                | Avro |
| ---            | ---- |
| Enum           | Yes  |
| Record         | Yes  |
| List           | Yes  |
| Map            | Yes  |
| Union          | Yes  |
| Recursive type | Yes |

* Recursive type means something like trees.

## Performance

### a thousand of 64-bit integers (most of them are quite small)

case id: case-f71f37ce

|      | size  | serialize | deserialize |
| ---  | ----: | --------: | ----------: |
| avro | 4,096 | 17,448 ns | 15,755 ns   |

### a thousand of binaries, each is 8-byte long

case id: case-1d6cec68

|             | size   | serialize | deserialize |
| ---         | ---:   | --------: | ----------: |
| avro(fixed) |  8,192 |  9,552 ns |  42,408 ns  |
| avro(bytes) | 12,288 | 17,763 ns | 111,197 ns  |

### a thousand of binaries, each is 1000-byte long

case id: case-9df88f5a

|             | size      | serialize  | deserialize |
| ---         | ---:      | --------:  | ----------: |
| avro(fixed) | 1,003,520 | 344,512 ns | 962,996 ns  |
| avro(bytes) | 1,003,520 | 144,622 ns | 305,392 ns  |

### a binary, of 1MB long

case id: case-7cfc53ac

|             | size      | serialize  | deserialize |
| ---         | ---:      | --------:  | ----------: |
| avro(fixed) | 1,048,576 | 114,521 ns | 359,782 ns  |
| avro(bytes) | 1,052,672 | 130,312 ns | 149,823 ns  |

### a thousand of strings, each is 8-byte long

case id: case-bc64e0e8

|      | size   | serialize | deserialize |
| ---  | ---:   | --------: | ----------: |
| avro | 12,288 | 17,599 ns | 58,275 ns   |

### a thousand of strings, each is 1000-byte long

case id: case-67764142

|      | size      | serialize  | deserialize  |
| ---  | ---:      | --------:  | ----------:  |
| avro | 1,003,520 | 134,130 ns | 309,259 ns   |

### a string, of 1MB-byte long

case id: case-58e1a854

|      | size      | serialize  | deserialize  |
| ---  | ---:      | --------:  | ----------:  |
| avro | 1,052,672 | 124,766 ns | 154,306 ns   |

## Comments

* Avro stores schema and data separately.
  Clients and servers can take care of schemas in highly customized ways.
  They can communicate schemas during handshaking to provide bi-directional compatibility.
  Or they can take schemas as common knowledge so they do not talk about them at all.

