import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Grid{

    private int[][] grid;
    private int id_code;
    private ReadWriteLock lock;

    public Grid(int amount){
        this.id_code = 0;
        this.lock = new ReentrantReadWriteLock();
        grid = new int[ConfigGlobal.size][ConfigGlobal.size];
        for (int i = 0; i < ConfigGlobal.size; i++){
            for (int j = 0; j < ConfigGlobal.size; j++){
                grid[i][j] = 0; // 0 significa que não tem trotinetes
            }
        }
        while (amount>0){
            int x = (int) (Math.random() * ConfigGlobal.size);
            int y = (int) (Math.random() * ConfigGlobal.size);
            grid[x][y] += 1;
            amount--;
        }
    }

    public void insertScooter(int x, int y){
        this.lock.writeLock().lock();
        grid[x][y] += 1; 
        this.lock.writeLock().unlock();
    }

    public void removeScooter(int x, int y){
        this.lock.writeLock().lock();
        grid[x][y] -= 1;
        this.lock.writeLock().unlock();
    }

    public int getScooterCount(int x, int y){
        this.lock.readLock().lock();
        int value = grid[x][y];
        this.lock.readLock().unlock();
        return value;
    }

    public List<Pos> checkAvailability(Pos start){
        
        int minx=start.getX()-ConfigGlobal.radius;
        if (minx < 0) minx = 0;
        int maxx=start.getX()+ConfigGlobal.radius;
        if (maxx >= ConfigGlobal.size) maxx = ConfigGlobal.size-1;
        int miny=start.getY()-ConfigGlobal.radius;
        if (miny < 0) miny = 0;
        int maxy=start.getY()+ConfigGlobal.radius;
        if (maxy >= ConfigGlobal.size) maxy = ConfigGlobal.size-1;
        List<Pos> posList = new ArrayList<Pos>();
        
        this.lock.readLock().lock();

        for (int i = miny; i <= maxy; i++){
            for (int j = minx; j <= maxx; j++){
                if (grid[i][j] > 0 && Math.abs(i-start.getY()) + Math.abs(j-start.getX()) <= ConfigGlobal.radius){
                    posList.add(new Pos(j, i));
                }
            }
        }
        this.lock.readLock().unlock();
        return posList;
    }

    
    public Reserve rentScotter(Pos start){
        int minx=start.getX() - ConfigGlobal.radius;
        if (minx < 0) minx = 0;
        int maxx=start.getX() + ConfigGlobal.radius;
        if (maxx >= ConfigGlobal.size) maxx = ConfigGlobal.size-1;
        int miny=start.getY() - ConfigGlobal.radius;
        if (miny < 0) miny = 0;
        int maxy=start.getY() + ConfigGlobal.radius;
        if (maxy >= ConfigGlobal.size) maxy = ConfigGlobal.size-1;
        Reserve reserve = null;
        List<Pos> posList = new ArrayList<Pos>();
        this.lock.writeLock().lock();
        for (int i = miny; i <= maxy; i++){
            for (int j = minx; j <= maxx; j++){
                if (grid[i][j] > 0 && Math.abs(i-start.getY()) + Math.abs(j-start.getX()) <= ConfigGlobal.radius){
                    posList.add(new Pos(j, i));
                    break;
                }
            }
        }
        
        if (posList.size() == 0){
            this.lock.writeLock().unlock();
            return (new Reserve(-1, new Pos(-1, -1)));
        }
        
        posList.sort((p1, p2) -> {
            int d1 = Math.abs(p1.getX() - start.getX()) + Math.abs(p1.getY() - start.getY());
            int d2 = Math.abs(p2.getX() - start.getX()) + Math.abs(p2.getY() - start.getY());
            return d1 - d2;
        });
        
        int i = posList.get(0).getX();
        int j = posList.get(0).getY();
        grid[j][i] -= 1;
        int id=id_code++;
        this.lock.writeLock().unlock();
        
        reserve = new Reserve(id, new Pos(i, j));

        return reserve;
    }
    
    public Price returnScooter(Reserve reserve, double discount){
        this.lock.writeLock().lock();
        grid[reserve.getEnd().getY()][reserve.getEnd().getX()] += 1;
        this.lock.writeLock().unlock();
        int distance = reserve.getDistance();
        int time = ConfigGlobal.calculateDifference(reserve.getTimeStart(), reserve.getTimeEnd());
        Price price = new Price(time, distance, discount); 
        return price;
    }

    public int[][] getGrid(){
        int[][] copy = new int[ConfigGlobal.size][ConfigGlobal.size];
        for (int i = 0; i < ConfigGlobal.size; i++){
            for (int j = 0; j < ConfigGlobal.size; j++){
                copy[i][j] = grid[i][j];
            }
        }
        return copy;
    }
    
    public String toString(){
        String s = "";
        for (int i = 0; i < ConfigGlobal.size; i++){
            for (int j = 0; j < ConfigGlobal.size; j++){
                s += String.format("[%3d]", grid[i][j]);
                s += " ";
            }
            s += "\n";
        }
        return s;
    }
}