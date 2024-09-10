import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.io.IOException;

public class Price{
    
    private double price;
    private double discount;

    public Price(double price, double discount) {
        this.price = price;
        this.discount = discount;
    }

    public Price(int time, int distance) {
        this.price = generatePrice(time, distance);
        this.discount = 0;
    }

    public Price(int time, int distance, double discount) {
        this.price = generatePrice(time, distance);
        this.discount = discount;
    }

    public double getPrice() {
        return price;
    }

    public double getDiscount() {
        return discount;
    }

    public double getFinalPrice() {
        return price - (price * discount);
    }

    public double generatePrice(double time, int distance) {
        return (time * 0.5) + (distance);
    }

    public String toString() {
        String s = "Price: (";
        s += "Normal price: " + price;
        s += ", Discount: " + discount;
        s += ", Final price: " + getFinalPrice() + ")";
        return s;
    }

    public static void serialize(Price p, DataOutputStream out) throws IOException {
        out.writeDouble(p.getPrice());
        out.writeDouble(p.getDiscount());
    }

    public static Price deserialize(DataInputStream in) throws IOException {
        double price = in.readDouble();
        double discount= in.readDouble();
        return new Price(price, discount);
    }
}
