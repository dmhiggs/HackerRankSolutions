TEST CASES

test case 0 
  input
    4 3
    <tag1 value = "HelloWorld">
    <tag2 name = "Name1">
    </tag2>
    </tag1>
    tag1.tag2~name
    tag1~name
    tag1~value

  output
    Name1
    Not Found!
    HelloWorld

test case 4
  input
    16 14
    <tag1 v1 = "123" v2 = "43.4" v3 = "hello">
    </tag1>
    <tag2 v4 = "v2" name = "Tag2">
    <tag3 v1 = "Hello" v2 = "World!">
    </tag3>
    <tag4 v1 = "Hello" v2 = "Universe!">
    </tag4>
    </tag2>
    <tag5>
    <tag7 new_val = "New">
    </tag7>
    </tag5>
    <tag6>
    <tag8 intval = "34" floatval = "9.845">
    </tag8>
    </tag6>
    tag1~v1
    tag1~v2
    tag1~v3
    tag4~v2
    tag2.tag4~v1
    tag2.tag4~v2
    tag2.tag3~v2
    tag5.tag7~new_val
    tag5~new_val
    tag7~new_val
    tag6.tag8~intval
    tag6.tag8~floatval
    tag6.tag8~val
    tag8~intval

  output
    123
    43.4
    hello
    Not Found!
    Hello
    Universe!
    World!
    New
    Not Found!
    Not Found!
    34
    9.845
    Not Found!
    Not Found!