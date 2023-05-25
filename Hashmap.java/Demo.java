public class Demo {
    public static void main(String[] args) {
        Hashmap<String, String> map = new Hashmap<>();
        System.out.printf("size: %d\n", map.size());
        System.out.printf("put apple pingguo: %s\n", map.put("apple", "pingguo"));
        System.out.printf("put banana xiangjiao: %s\n", map.put("banana", "xiangjiao"));
        System.out.printf("put orange chengzi: %s\n", map.put("orange", "chengzi"));
        System.out.printf("size: %d\n", map.size());
        System.out.printf("get apple: %s\n", map.get("apple"));
        System.out.printf("get banana: %s\n", map.get("banana"));
        System.out.printf("get orange: %s\n", map.get("orange"));
        System.out.printf("get pear: %s\n", map.get("pear"));
        System.out.printf("remove apple: %s\n", map.remove("apple"));
        System.out.printf("remove pear: %s\n", map.remove("pear"));
        System.out.printf("size: %d\n", map.size());
        System.out.printf("get apple: %s\n", map.get("apple"));
        System.out.printf("get banana: %s\n", map.get("banana"));
        System.out.printf("size: %d\n", map.size());
    }
}

/*
Output:
size: 0
put apple pingguo: null
put banana xiangjiao: null
put orange chengzi: null
size: 3
get apple: pingguo
get banana: xiangjiao
get orange: chengzi
get pear: null
remove apple: pingguo
remove pear: null
size: 3
get apple: null
get banana: xiangjiao
size: 3
*/
