# serializer-combat
Comparison between several serializers in C++.

We have following candidates:
* [Avro-1.8](http://avro.apache.org/docs/1.8.1/)
* [Cap'n'Proto](https://capnproto.org/)
* ProtoBuf-2 (under construction)
* ProtoBuf-3 (under construction)
* Msgpack (under construction)
* Thrift (under construction)
* FlatBuffers (under construction)
* RapidJson (under construction)

## General

|                   | Avro    | Cap'n'Proto  |
| ---               | ----    | -----------  |
| Sponsor           | Hadoop  | Sandstorm.io |
| Format spec       | Yes     | Yes          |
| Plain-text format | JSON    | No           |
| Binary format     | Yes     | Yes          |
| Code generation   | Yes     | Yes          |
| Handshaking       | Yes     | No           |
| Dynamic typing    | Yes     | No           |
| Message framing   | Yes     | Yes          |

* The purpose of the handshake is to ensure that the client and the server have each other's protocol definition, so that the client can correctly deserialize responses, and the server can correctly deserialize requests.
* Dynamic typing means the reader does not need any predefined schema to read any valid messages.
* Message framing means the reader and the writer does not necessarily read from/write to a single consecutive buffer.
* The author of Cap'n'Proto was the primary author of Protocol Buffers version 2.

## Language Support

|         | Avro | Cap'n'Proto |
| ---     | ---- | ----------- |
| C       | Yes  | Yes         |
| C++     | 98   | 11          |
| JAVA    | Yes  | Yes         |
| C#      | Yes  | Yes         |
| Python  | 2/3  | 2           |
| Node.js | Yes  | Yes         |
| PHP     | Yes  | Yes         |
| Ruby    | Yes  | Yes         |
| Go      | Yes  | Yes         |

* Go support for Avro is not official.
* Language supports for Cap'n'Proto, except C++11, are not official.

## Data Types

### Primitive types

|         | Avro          | Cap'n'Proto   |
| ---     | ----          | -----------   |
| Integer | 32/64         | 8/16/32/64    |
| Float   | single/double | single/double |
| String  | UTF-8         | UTF-8         |
| Binary  | dynamic/fixed | dynamic       |

### Complex types

|                | Avro | Cap'n'Proto |
| ---            | ---- | ----------- |
| Enum           | Yes  | Yes         |
| Record         | Yes  | Yes         |
| List           | Yes  | Yes         |
| Map            | Yes  | No          |
| Union          | Yes  | Yes         |
| Recursive type | Yes  | Yes         |

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

