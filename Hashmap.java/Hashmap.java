import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Hashmap<K, V> extends AbstractMap<K, V> {
    int capacity;
    int size;
    List<Node> table;
    class Node {
        K key;
        V value;
        Node next;
        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }
    }

    public Hashmap() {
        this(32);
    }

    public Hashmap(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.table = new ArrayList<>(capacity);
        for (int i = 0; i < capacity; i++) {
            table.add(null);
        }
    }

    private int getIndex(Object key) {
        return ((key.hashCode() % capacity) + capacity) % capacity;
    }

    @Override
    public V get(Object key) {
        int index = getIndex(key);
        Node current = table.get(index);
        while (current != null) {
            if (current.key.equals(key)) {
                return current.value;
            }
        }
        return null;
    }

    @Override
    public V put(K key, V value) {
        int index = getIndex(key);
        Node current = table.get(index);
        if (current == null) {
            table.set(index, new Node(key, value));
            size++;
            return null;
        }
        Node previous = null;
        while (current != null) {
            if (current.key.equals(key)) {
                V oldValue = current.value;
                current.value = value;
                return oldValue;
            }
            previous = current;
            current = current.next;
        }
        previous.next = new Node(key, value);
        return null;
    }

    @Override
    public V remove(Object key) {
        int index = getIndex(key);
        Node current = table.get(index);
        Node previous = null;
        while (current != null) {
            if (current.key.equals(key)) {
                if (previous == null) {
                    this.table.set(index, null);
                } else {
                    previous.next = current.next;
                }
                return current.value;
            }
            previous = current;
            current = current.next;
        }
        return null;
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }
    
    @Override
    public int size() {
        return this.size;
    }

    @Override
    public Set<Map.Entry<K,V>> entrySet() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'entrySet'");
    }
    
}